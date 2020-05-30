#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include "Pacemaker.hpp"
#include "KeyBuffer.hpp"
#include "ChartBuilder.hpp"
#include "Alice.hpp"
#include "Singletons.hpp"
#include "Mook.hpp"
#include "SFML/Audio.hpp"
#include "TraceRenderer.hpp"
#include "Graphics/g3d/Line.hpp"
#include "Graphics/g3d/Panel.hpp"
#include "EditorChart.hpp"
#include "EditorTap.hpp"
#include "EditorNoteBuilder.hpp"
#include "EditorTraceBuilder.hpp"
#include "Effector.hpp"
#include "Nice.hpp"
#include "Bad.hpp"
#include "Sky.hpp"
#include "Effector.hpp"
#include "Nice.hpp"

namespace otoge2019 {
  /// エディターを提供する
  /// Pacemaker, Chart, Music, Alice, BG, Effect, KeyBuffer
  /// Noteとトレースのデフォルトグラフィックはすでに設定してあるとする
  class EditorFrame {
    private:
      Pacemaker pacemaker;
      sf::Music music;
      std::string chartpath;
      KeyBuffer keyBuffer;
      EditorChart chart; //> Aliceに渡すためだけのchart
      Sky sky;
      int keyRepeatCounter; //> キーリピート
      int keyRepeatThreasholds; //> キーリピートのフレーム

      Effector effector; //> 保存したことを通知

      std::unique_ptr<Graphics::g3d::Panel> focusPanel;

      // データ構造
      std::shared_ptr<std::vector<std::shared_ptr<Trace>>> traces;
      std::shared_ptr<std::vector<std::shared_ptr<Note>>> notes;
      std::vector<std::shared_ptr<Trace>>::iterator traceitr;

      // 出力

      void exportChart();
      /// @fn
      /// トレースを書き出す
      void exportTrace();

      /// @fn
      /// ノーツを書き出す
      void exportNote();

      // フォーカス関連

      /// @fn
      /// フォーカスパネルを移動させる
      void redrawForcus();

      /// @fn
      /// 現在時刻に最も近いトレースを選択する
      std::vector<std::shared_ptr<Trace>>::iterator focusNearest();
      /// @fn
      /// 次のトレースを選択
      std::vector<std::shared_ptr<Trace>>::iterator focusNext();
      /// @fn
      /// 前のトレースを選択
      std::vector<std::shared_ptr<Trace>>::iterator focusPrev();

      /// @fn
      /// 現在時刻に直前のトレースを選択する
      std::vector<std::shared_ptr<Trace>>::iterator getLatestTrace();

      /// @fn
      /// 現在選択中のトレースにノーツを挿入する(重複検査なし)
      void insertNote(ButtonIdentifier);

      /// @fn
      /// 現在選択中のトレースのノーツを削除する(重複していたら全削除)
      void deleteNote(ButtonIdentifier);

      /// @fn
      /// 現在時刻にトレースを挿入する
      void insertTrace();
      /// @fn
      /// フォーカストレースを削除する
      void deleteTrace();
      /// @fn
      /// 選択中のトレースを移動させる
      void moveTrace(double seconds, double height);

      std::shared_ptr<Alice> alice;
      std::unique_ptr<TraceRenderer> traceRenderer; //> トレース描画
      GLfloat winder; //> 時間操作用
      bool paused; //> 一時停止しているか(winderかgetOffsetか)

      Graphics::g3d::Line line;

      /// put_scoreに登録してエフェクトを発生させる
      void test_put_effect(Judge, GLfloat, GLfloat);

    public:
      EditorFrame(double scale, std::string chartpath);
      /// @fn
      /// 準備をする
      /// Chart, Music, Alice, KeyBuffer, BG, (Effect)を準備
      void prepare();
      /// @fn
      /// 毎フレーム呼ばれる
      void routine();
  };
}
