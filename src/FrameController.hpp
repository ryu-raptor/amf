#pragma once
#include <memory>
#include <vector>

namespace otoge2019 {
  class Frame;

  class FrameController {
    private:
      bool exitFlag;
      std::shared_ptr<Frame> currentFrame;
      std::shared_ptr<Frame> nextFrame;
    public:
      FrameController();
      void set(std::shared_ptr<Frame>);
      void segue(std::shared_ptr<Frame>);
      void routine();
      bool getStatus();
      void exit();
  };
}
