#include "Chart.hpp"
#include <vector>
#include <iostream>

namespace otoge2019 {
  void Chart::ButtonBuffer::set(ButtonIdentifier bi, KeyBuffer::KeyState ks)
  {
    states[bi] = ks;
  }

  KeyBuffer::KeyState Chart::ButtonBuffer::get(ButtonIdentifier bi)
  {
    return states[bi];
  }

  Chart::Chart()
  {
    // finalizeVectorを作成する
    finalizeVector.reset(new std::vector<std::shared_ptr<Note>>());
  }

  void Chart::routine()
  {
    // checkstate
    // 描画
    // トレース
    // ノーツ
    for (int bi = 0; bi < 2; bi++) {
      for (auto nptr : *notes[bi]) {
        nptr->render();
      }
    }
    //finalizer();
  }

  void Chart::checkState(ButtonBuffer kb, double seconds)
  {
    // Judge.md参照
    // enumにforeachがあればいいのだが
    // enum classにはできる.
    for (auto bi : {Upper, Lower} ) {
      check(kb, bi, seconds);
    }
  }

  // 挑戦的な関数
  void Chart::check(Chart::ButtonBuffer kb, ButtonIdentifier bi, double seconds)
  {
    if (notes[bi]->size() == 0) {
      return;
    }
    auto ks = kb.get(bi); // キーの押下状態
    auto target = notes[bi]->begin(); //getMetricallyMinimumNote(bi, 0); // 一番0からのメトリックの小さいノーツを選択(先頭のノーツを取ると未ソートの場合うまくいかない)
    // 処理をする
    auto result = (*target)->state(ks, seconds);
    // 開放していいのなら削除
    if (result == Note::Result::release) {
      finalizeVector->push_back(*target);
      notes[bi]->erase(target);
    }
  }

  void Chart::finalizer()
  {
    for (auto itr = finalizeVector->begin(); itr != finalizeVector->end(); ) {
      auto ptr = *itr;
      if (!ptr->isFinished()) {
        ptr->scheduledTask();
      }
      else {
        //delete ptr;
        itr = finalizeVector->erase(itr);
        continue;
      }
      itr++;
    }
  }

  Trace Chart::getTrace(unsigned int index)
  {
    return traces->at(index);
  }

  int Chart::getTracesSize()
  {
    return traces->size();
  }

  int Chart::getLatestTraceIndex(double seconds)
  {
    int index = -1;
    int i;
    for (i = 0; i < traces->size(); i++) {
      if ((*traces)[i].seconds > seconds)
      {
        break;
      }
    }
    index = i - 1;
    return index;
  }

  // Judge.md参照
  int Chart::getLatestNoteIndex(ButtonIdentifier bi, double seconds)
  {
    double minimalMetric = 100000;
    int least = notes[bi]->size() - 1;
    for (auto i = 0; i < notes[bi]->size(); i++) {
      auto metric = (*notes[bi])[i]->metric(seconds);
      // 一緒はダメ. 一緒の時は手前のノーツが優先されるため
      if (minimalMetric > metric) {
        minimalMetric = metric;
        least = i;
      }
      // メトリックが大きくなった地点でそれ以降はチェック不要
      else {
        break;
      }
    }

    return least;
  }

  std::vector<std::shared_ptr<Note>>::iterator Chart::getMetricallyMinimumNote(ButtonIdentifier bi, double seconds)
  {
    if (notes[bi]->size() == 0) {
      throw std::out_of_range("最小のメトリックなんてバカらしい");
    }
    auto minimal = notes[bi]->begin();
    double minimalMetric = (*minimal)->metric(seconds);
    for (auto itr = minimal + 1; itr < notes[bi]->end(); itr++) {
      auto metric = (*itr)->metric(seconds);
      if (metric < minimalMetric) {
        minimal = itr;
        minimalMetric = metric;
      }
    }
    return minimal;
  }

} // namespace otoge2019
