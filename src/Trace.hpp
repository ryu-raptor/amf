#pragma once

namespace otoge2019 {
  /// トレースノード
  /// 譜面の基本要素
  struct Trace
  {
    double seconds;
    double height;
    double position; //> Pacemakerによって位置を調整されている.
  };
} // namespace otoge2019
