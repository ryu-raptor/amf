#pragma once
#include <memory>
#include <string>
#include "Chart.hpp"
#include "Pacemaker.hpp"
#include "Graphics/g3d/Panel.hpp"
#include "Graphics/Texture.hpp"
#include "Followee.hpp"

namespace otoge2019 {
  /// 自キャラ
  /// グラフィクス, キー入力ハンドラ
  class Alice : public Followee
  {
    private:
      Follower* follower;
      Chart *chart;
      Graphics::Texture *texture;
      Pacemaker* pacemaker;
      unsigned int latestTraceIndex; //>最後に踏んだトレースの番号
      double gradient; //> アリスの回転に用いる傾き(上に行くときにちょっと傾くべき)

      /// 二つのトレースとアリスの現在時刻からアリスの高さを求める
      /// 直角の時などに特別な処理が必要.
      double linearInterpolation(Trace*, Trace*, double, Trace *&responce, double*);
      /// 現在時刻に最も近い後ろにいるトレースを削除
      int getLatestTraceIndex(double seconds);

    public:
      std::unique_ptr<Graphics::g3d::Panel> graphic; //>アリスの画像
      Alice(std::string, Chart*, Pacemaker*);
      ~Alice();

      /// アリスの位置を変更
      void update();
      /// アリスの現在の高さを取得
      /// ついでに回転も更新する
      double getHeight();
      /// 描画
      void render();
      /// 純粋仮想関数たち
      void followee(Follower*);
      ///
      void setAlpha(double);
  };
} // namespace otoge2019
