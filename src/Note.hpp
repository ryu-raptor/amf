#pragma once

#include <functional>
#include <memory>
#include "Schedulable.hpp"
#include "ButtonIdentifier.hpp"
#include "KeyBuffer.hpp"
#include "Graphics/g3d/Panel.hpp"

namespace otoge2019 {
  enum class Judge {
    Nice, Bad
  };

  class Note : public Schedulable
  {
    protected:
      static std::function<void(Judge, GLfloat, GLfloat)> putScore;
      static double judgeThreasholds;
      static GLfloat laneHeightOffset; //> トレース線に対して上下にどれだけ動くか(ButtonIdentifierで決定)
      
      std::unique_ptr<Graphics::g3d::Panel> panel; //> ノーツのグラフィックを格納する
      bool scored; //> スコアを算出したか? (finalizeVector入りしたらmissとして自動的にtrueにする
      bool disappeared; //> 画面から消える処理を完了したか?
    public:
      enum Result {keep, release};

      /// @fn
      /// 描画をする
      virtual void render() = 0;
      
      static void setPutScoreCallback(std::function<void(Judge, GLfloat, GLfloat)>);
      /// @fn
      /// 単純なリソースファイルを読み込む
      /// Resources.mdを参照
      static void loadNoteGraphic(std::string resourcepath);
      /// @return 開放されてもいいか?
      virtual Result state(KeyBuffer::KeyState, double seconds) = 0;
      virtual double metric(double seconds) = 0;
  };
} // namespace otoge2019

