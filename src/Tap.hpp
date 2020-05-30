#pragma once

#include <memory>
#include "Note.hpp"
#include "Trace.hpp"
#include "ResourceFiler.hpp"
#include "Graphics/g3d/Panel.hpp"
#include "Graphics/g3d/DuplicatedPanel.hpp"

namespace otoge2019 {
  class Tap : public Note {
    protected:
      Trace trace;
      static std::shared_ptr<Graphics::g3d::Panel> pointSource; //> タップ点のグラフィックの素
      static double forwardMissThreasholds; //> 早押しミスの閾値
      std::unique_ptr<Graphics::g3d::DuplicatedPanel> point; //> タップ点のグラフィック

      bool scored;

      Tap(); //> 継承用デフォルトコンストラクタ
      
    public:
      Tap(ButtonIdentifier, Trace trace);
      virtual Result state(KeyBuffer::KeyState, double seconds);
      virtual double metric(double seconds);

      virtual void render();

      static void loadNoteGraphic(ResourceFiler resource);
      bool isFinished();
      // クロージャによって動的に生成された関数を実行する
      void scheduledTask();
  };
} // namespace otoge2019
