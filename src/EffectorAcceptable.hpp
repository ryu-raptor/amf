#pragma once


namespace otoge2019 {
  class EffectorAcceptable {
    public:
      virtual void render() = 0;
      virtual bool isFinished() = 0;
  };
} // namespace otoge2019
