#include "FrameController.hpp"
#include "Frame.hpp"

namespace otoge2019 {
  void FrameController::set(std::shared_ptr<Frame> frame)
  {
    currentFrame = frame;
    currentFrame->setFrameController(this);
    currentFrame->prepare();
    currentFrame->show();
  }

  void FrameController::segue(std::shared_ptr<Frame> next)
  {
    next->prepare();
    currentFrame->dismiss();
    next->show();
    next->setFrameController(this);
    nextFrame = next;
  }

  FrameController::FrameController() {
    exitFlag = false;
  }

  void FrameController::routine()
  {
    if (nextFrame) {
      currentFrame = nextFrame;
      nextFrame.reset();
    }
    currentFrame->routine();
  }

  bool FrameController::getStatus()
  {
    return exitFlag;
  }

  void FrameController::exit()
  {
    exitFlag = true;
    currentFrame->dismiss();
    currentFrame.reset();
  }
}
