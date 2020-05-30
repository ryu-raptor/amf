#pragma once
#include <memory>
#include "FrameController.hpp"

namespace otoge2019 {
  class Frame {
    protected:
      FrameController* frameController;
    public:
      void setFrameController(FrameController*);
      virtual void show();
      virtual void dismiss();
      virtual void prepare() = 0;
      virtual void routine() = 0;
  };
} // namespace otoge2019

