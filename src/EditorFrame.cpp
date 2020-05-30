#include "EditorFrame.hpp"
#include "Singletons.hpp"

namespace otoge2019 {

  void EditorFrame::exportChart()
  {
  }

  void EditorFrame::exportTrace()
  {
    auto tracepath = chartpath + "/trace";
    std::ofstream stream(tracepath);
    if (stream.fail()) {
      throw std::ios::failure("トレースファイルのオープンに失敗");
    }
    // 書き出し(最初と最後に必ずトレースがあるという仮定のもとtraces->end() - 1を終了条件にしている
    for (auto itr = traces->begin() + 1; itr != traces->end() - 1; itr++) {
      auto traceptr = *itr;
      stream << traceptr->seconds << " " << traceptr->height << std::endl;
    }
  }

  /// @fn
  /// ノーツを書き出す
  /// n^2に比例する
  void EditorFrame::exportNote()
  {
    auto tracepath = chartpath + "/note";
    std::ofstream stream(tracepath);
    if (stream.fail()) {
      throw std::ios::failure("ノーツファイルのオープンに失敗");
    }

    // ソート(メトリックで)
    std::sort(notes->begin(), notes->end(),
              [](std::shared_ptr<Note> x, std::shared_ptr<Note> y) {
                return x->metric(0) < y->metric(0);
              }
             );


    // 書き出し
    for (auto nptr : *notes) {
      // アップキャスト
      auto etap = dynamic_cast<EditorTap*>(nptr.get());
      if (etap != nullptr) {
        // トレースのインデックスを取得する(こいつがボトルネック)
        auto tptr = etap->getTrace();
        int index;
        for (index = 1; index < traces->size() - 1; index++) {
          if (tptr == traces->at(index)) {
            break;
          }
        }
        index -= 1; // 最初のトレースを除去しているのでその分減らす
        if (index < 0) continue;

        if (etap->getButtonIdentifier() == ButtonIdentifier::Upper) {
          stream << "0 ";
        }
        else {
          stream << "1 ";
        }
        // Tapしかないので
        stream << "0 ";

        // 書き出す
        stream << index << std::endl;
      }
    }
  }

  /// @fn
  /// 現在選択中のトレースにノーツを挿入する(重複検査なし)
  void EditorFrame::insertNote(ButtonIdentifier bi)
  {
    notes->push_back(std::shared_ptr<Note>(new EditorTap(bi, *traceitr)));
    focusNext();
  }

  /// @fn
  /// 現在選択中のトレースのノーツを削除する(重複していたら全削除)
  void EditorFrame::deleteNote(ButtonIdentifier bi)
  {
    for (auto itr = notes->begin(); itr != notes->end();) {
      auto etap = dynamic_cast<EditorTap*>((*itr).get());
      if (etap != nullptr) {
        if (etap->doesBelong(bi) && etap->hasTrace(*traceitr)) {
          itr = notes->erase(itr);
          continue;
        }
      }

      itr++;
    }
  }

  /// @fn
  /// フォーカスパネルを移動させる
  void EditorFrame::redrawForcus()
  {
    auto ptr = *traceitr;
    focusPanel->setPosition(ptr->position, ptr->height, 0.0f);
  }

  /// @fn
  /// 現在時刻に最も近いトレースを選択する
  std::vector<std::shared_ptr<Trace>>::iterator EditorFrame::focusNearest()
  {
    auto latestitr = traces->begin();
    double minimalest = std::abs((*latestitr)->position - pacemaker.getAlicePosition());
    for (auto itr = ++latestitr; itr != traces->end(); itr++) {
      auto metric = std::abs((*itr)->position - pacemaker.getAlicePosition());
      if (minimalest > metric) {
        minimalest = metric;
        latestitr = itr;
      }
      else {
        break;
      }
    }
    traceitr = latestitr;
    redrawForcus();
    return traceitr;
  }

  /// @fn
  /// 次のトレースを選択
  std::vector<std::shared_ptr<Trace>>::iterator EditorFrame::focusNext()
  {
    if (traceitr != traces->end() - 1) {
      ++traceitr;
    }
    redrawForcus();
    return traceitr;
  }

  /// @fn
  /// 前のトレースを選択
  std::vector<std::shared_ptr<Trace>>::iterator EditorFrame::focusPrev()
  {
    if (traceitr != traces->begin()) {
      --traceitr;
    }
    redrawForcus();
    return traceitr;
  }

  /// @fn
  /// 現在時刻に直前のトレースを選択する(これはトレース挿入のヒントに用いる)
  std::vector<std::shared_ptr<Trace>>::iterator EditorFrame::getLatestTrace()
  {
    auto itr = traces->begin();
    double p = pacemaker.getAlicePosition();
    for (; itr != traces->end(); itr++) {
      // 符号が正になったとき抜ける
      if ((*itr)->position - p > 0) {
        // 一個もどす
        // beginの前に行くことがあるのでチェック
        if (itr != traces->begin()) {
          itr--;
        }
        break;
      }
    }
    return itr;
  }

  /// @fn
  /// 現在時刻にトレースを挿入する
  void EditorFrame::insertTrace()
  {
    // 現在時刻の直前のトレースを取得する
    auto itr = getLatestTrace();
    auto ipos = itr + 1; //> 直後の位置の挿入
    double p = pacemaker.getAlicePosition();

    std::shared_ptr<Trace> t(new Trace());
    t->position = p;
    t->seconds = pacemaker.getSeconds(p);
    t->height = alice->getHeight();
    // insertはその位置に入れて, その位置にあったもの以降を後ろへシフト
    traces->insert(ipos, t);
    // イテレータを更新
    focusNearest();
  }

  /// @fn
  /// フォーカストレースを削除する
  /// 所属しているノーツは全て削除
  void EditorFrame::deleteTrace()
  {
    deleteNote(ButtonIdentifier::Upper);
    deleteNote(ButtonIdentifier::Lower);
    traceitr = traces->erase(traceitr);
    redrawForcus();
  }

  /// @fn
  /// 選択中のトレースを移動させる
  ///
  /// @param (seconds) 移動量
  /// @param (height) 移動量
  void EditorFrame::moveTrace(double seconds, double height)
  {
    auto ptr = *traceitr;
    ptr->seconds += seconds;
    ptr->height += height;
    ptr->position = pacemaker.getPosition(ptr->seconds);
    redrawForcus();
  }

  void EditorFrame::test_put_effect(Judge j, GLfloat x, GLfloat y)
  {
    if (j == Judge::Nice) {
      effector.add(std::shared_ptr<EffectorAcceptable>(new Nice(x, y)));
    }
    else {
      effector.add(std::shared_ptr<EffectorAcceptable>(new Bad(x, y)));
    }
  }

  EditorFrame::EditorFrame(double scale, std::string chartpath) {
    // ペースメーカをコンストラクトしておく
    pacemaker.setScale(scale);
    this->chartpath = chartpath;
  }

  void EditorFrame::prepare()
  {
    // この部分は与えられた方がいい
    ResourceFiler rf("ResourceInfo.ini");
    auto resourcedir = rf.get("root", "ResourceDirectory");
    rf.append(resourcedir + "/" + "ResourceInfo.ini");
    resourcedir = rf.get("Trace", "ResourceDirectory");
    rf.append(resourcedir + "/" + "ResourceInfo.ini");
    //==============
    traceRenderer.reset(new TraceRenderer(resourcedir + "/" + rf.get("Trace", "Graphic")));
    focusPanel.reset(new Graphics::g3d::Panel(resourcedir + "/" + rf.get("Focus", "Graphic"), 0.01));
    sky.loadImage(rf.get("root", "ResourceDirectory") + "/Sky.png");

    // 既存のファイルを読み込む(どちらも揃ってないとダメ)
    try {
      EditorTraceBuilder tbuilder;
      EditorNoteBuilder nbuilder;
      traces = tbuilder.build(chartpath + "/trace", pacemaker);
      nbuilder.build(chartpath + "/note", traces);
      notes = nbuilder.get();
    } catch (...) {
      std::cout << "lacks chart file. re-generate" << std::endl;
      // vectorを初期化
      traces.reset(new std::vector<std::shared_ptr<Trace>>());
      notes.reset(new std::vector<std::shared_ptr<Note>>());

      // スタブトレースを挿入
      std::shared_ptr<Trace> t3(new Trace());
      t3->seconds = 0;
      t3->height = 0;
      t3->position = pacemaker.getPosition(t3->seconds);
      traces->push_back(t3);
    }
    // 補助トレースの挿入
    std::shared_ptr<Trace> t1(new Trace());
    t1->seconds = -100000;
    t1->height = 0;
    t1->position = pacemaker.getPosition(t1->seconds);
    traces->insert(traces->begin(), t1);
    std::shared_ptr<Trace> t2(new Trace());
    t2->seconds = 100000;
    t2->height = 0;
    t2->position = pacemaker.getPosition(t2->seconds);
    traces->push_back(t2);

    // chartをコンストラクト
    chart.setTrace(traces);

    // Mookにキーバッファを設定
    Mook::setKeyCallback([&] (int keycode, int scancode, int action, int mod) {
      keyBuffer.keyUpdate(keycode, action);
    });

    // Alice
    alice.reset(new Alice(rf.get("root", "ResourceDirectory") + "/" + rf.get("Alice", "Graphic"), &chart, &pacemaker));
    alice->followee(Singletons::cameraHolder.get());
    alice->setAlpha(0.5);

    // Effector
    Note::setPutScoreCallback([&](Judge j, GLfloat x, GLfloat y){
      this->test_put_effect(j, x, y);
    });

    // Music
    if (!music.openFromFile(chartpath + "/" + "song.ogg")) {
      throw std::ios::failure("曲のオープンに失敗しました");
    }

    pacemaker.setTickFunction([&]{
      if (paused) {
        return winder;
      }
      else {
        return music.getPlayingOffset().asSeconds();
      }
    });

    music.play();
    paused = false;

    // フォーカスさせておく
    focusNearest();
    keyRepeatCounter = keyRepeatThreasholds;
    keyRepeatThreasholds = 10;
  }

  void EditorFrame::routine()
  {
    keyBuffer.update();

    /// 一時停止か
    if (paused) {
      // 低速時間移動
      if (keyBuffer.getState(GLFW_KEY_LEFT_SHIFT) == KeyBuffer::KeyState::press &&
        keyBuffer.getState(GLFW_KEY_L) != KeyBuffer::KeyState::release) {
        winder += 0.01;
      }
      else if (keyBuffer.getState(GLFW_KEY_LEFT_SHIFT) == KeyBuffer::KeyState::press &&
        keyBuffer.getState(GLFW_KEY_H) != KeyBuffer::KeyState::release) {
        if (winder <= 0) winder = 0;
        else winder -= 0.01;
      }
      // 高速時間移動
      else if (keyBuffer.getState(GLFW_KEY_L) != KeyBuffer::KeyState::release) {
        winder += 0.1;
      }
      else if (keyBuffer.getState(GLFW_KEY_H) != KeyBuffer::KeyState::release) {
        if (winder <= 0) winder = 0;
        else winder -= 0.1;
      }

      // フォーカストレースの左右移動
      if (keyBuffer.getState(GLFW_KEY_LEFT_SHIFT) == KeyBuffer::KeyState::press &&
        keyBuffer.getState(GLFW_KEY_J) != KeyBuffer::KeyState::release) {
        moveTrace(-0.005, 0.0);
      }
      else if (keyBuffer.getState(GLFW_KEY_LEFT_SHIFT) == KeyBuffer::KeyState::press &&
        keyBuffer.getState(GLFW_KEY_K) != KeyBuffer::KeyState::release) {
        moveTrace(0.005, 0.0);
      }
      // トレースの上下
      else if (keyBuffer.getState(GLFW_KEY_J) == KeyBuffer::KeyState::press) {
        if (keyRepeatCounter++ >= keyRepeatThreasholds) {
          moveTrace(0, -0.5);
          keyRepeatCounter = 0;
        }
      }
      else if (keyBuffer.getState(GLFW_KEY_K) == KeyBuffer::KeyState::press) {
        if (keyRepeatCounter++ >= keyRepeatThreasholds) {
          moveTrace(0, +0.5);
          keyRepeatCounter = 0;
        }
      }
      else {
        keyRepeatCounter = keyRepeatThreasholds;
      }

      // 保存(Ctrl + S) (Ctrlは長押し, Sはヒットのみで何度も書くのを防ぐ)
      if ((keyBuffer.getState(GLFW_KEY_LEFT_CONTROL) == KeyBuffer::KeyState::press) 
          && (keyBuffer.getState(GLFW_KEY_S) == KeyBuffer::KeyState::hit)) {
        exportTrace();
        exportNote();
        auto pos = Singletons::cameraHolder->getPosition();
        test_put_effect(Judge::Nice, pos.x, pos.y);
        std::cout << "saved\n";
      }
    }

    // トレースの挿入
    if (keyBuffer.getState(GLFW_KEY_I) == KeyBuffer::KeyState::hit || keyBuffer.getState(GLFW_KEY_U) == KeyBuffer::KeyState::hit) {
      insertTrace();
    }
    // トレースの削除
    else if (keyBuffer.getState(GLFW_KEY_D) == KeyBuffer::KeyState::hit) {
      deleteTrace();
    }
    // トレースのフォーカス
    else if (keyBuffer.getState(GLFW_KEY_F) == KeyBuffer::KeyState::hit) {
      focusNearest();
    }
    else if (keyBuffer.getState(GLFW_KEY_N) == KeyBuffer::KeyState::hit) {
      focusNext();
    }
    else if (keyBuffer.getState(GLFW_KEY_P) == KeyBuffer::KeyState::hit) {
      focusPrev();
    }
    // ノーツの削除 (修飾キーの有無で判断するのでこっちが先. もうちょっと綺麗にしたい)
    else if (keyBuffer.getState(GLFW_KEY_UP) == KeyBuffer::KeyState::hit &&
             keyBuffer.getState(GLFW_KEY_LEFT_SHIFT) == KeyBuffer::KeyState::press) {
      deleteNote(ButtonIdentifier::Upper);
    }
    else if (keyBuffer.getState(GLFW_KEY_DOWN) == KeyBuffer::KeyState::hit &&
             keyBuffer.getState(GLFW_KEY_LEFT_SHIFT) == KeyBuffer::KeyState::press) {
      deleteNote(ButtonIdentifier::Lower);
    }
    // ノーツの挿入
    else if (keyBuffer.getState(GLFW_KEY_UP) == KeyBuffer::KeyState::hit) {
      insertNote(ButtonIdentifier::Upper);
    }
    else if (keyBuffer.getState(GLFW_KEY_DOWN) == KeyBuffer::KeyState::hit) {
      insertNote(ButtonIdentifier::Lower);
    }


    if (keyBuffer.getState(GLFW_KEY_SPACE) == KeyBuffer::KeyState::hit) {
      if (paused) {
        paused = false;
        music.setPlayingOffset(sf::seconds(winder));
        music.play();
      }
      else {
        paused = true;
        music.pause();
        // 現在の時間を記録
        winder = music.getPlayingOffset().asSeconds();
      }
    }

    // TEST: metric計算がちゃんとされているか確認
    sky.render();
    alice->update();
    for (auto nptr : *notes) {
      nptr->render();
    }
    focusPanel->renderWithDefault();
    traceRenderer->render(traces);
    alice->render();
    effector.routine();
    //line.draw(glm::vec3(0, 0, 0), glm::vec3(100, 0, 0), 1.0f);
  }
} // namespace otoge2019
