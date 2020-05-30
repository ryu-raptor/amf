#pragma once
#include <functional>

namespace otoge2019 {
  class Pacemaker
  {
    private:
      std::function<double()> getTick;
      double scale;
    public:
      /// 1秒を1としてその何倍か
      void setScale(double);
      void setTickFunction(std::function<double()>);
      /// 現在のアリスの位置を取得
      double getAlicePosition();
      /// 位置を取得
      double getPosition(double tick);
      /// 秒を取得
      double getSeconds(double position);
  };
} // namespace otoge2019
