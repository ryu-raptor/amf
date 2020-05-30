#include "EditorTap.hpp"
#include <cmath>
#include <iostream>

namespace otoge2019 {
  EditorTap::EditorTap(ButtonIdentifier bi, std::weak_ptr<Trace> trace)
  {
    etrace = trace;
    point.reset(new Graphics::g3d::DuplicatedPanel(*(pointSource.get())));
    sign = 1;
    if (bi == ButtonIdentifier::Upper) {
      sign = 1;
      point->setColorModulation(255, 0, 0);
    }
    else {
      sign = -1;
      point->setColorModulation(0, 0, 255);
    }

    if (auto ptr = etrace.lock()) {
      eheight = ptr->height + sign * laneHeightOffset;
      point->setPosition(ptr->position, eheight, 0);
    }
  }

  Note::Result EditorTap::state(KeyBuffer::KeyState, double seconds)
  {
    return Result::keep;
  }

  double EditorTap::metric(double seconds)
  {
    if (auto ptr = etrace.lock()) {
      return std::abs(ptr->seconds - seconds);
    }
    return 0;
  }

  bool EditorTap::hasTrace(std::shared_ptr<Trace> t)
  {
    if (auto ptr = etrace.lock()) {
      return t.get() == ptr.get();
    }
    return false;
  }

  bool EditorTap::doesBelong(ButtonIdentifier bi)
  {
    if (sign == 1) {
      return bi == ButtonIdentifier::Upper;
    }
    else {
      return bi == ButtonIdentifier::Lower;
    }
  }

  std::shared_ptr<Trace> EditorTap::getTrace()
  {
    return etrace.lock();
  }

  ButtonIdentifier EditorTap::getButtonIdentifier()
  {
    if (sign == 1) {
      return ButtonIdentifier::Upper;
    }
    else {
      return ButtonIdentifier::Lower;
    }
  }

  void EditorTap::render()
  {
    // 位置を更新する
    if (auto ptr = etrace.lock()) {
      eheight = ptr->height + sign * laneHeightOffset;
      point->setPosition(ptr->position, eheight, 0);
      point->renderWithDefault();
    }
  }
} // namespace otoge2019
