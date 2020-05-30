#include "Pacemaker.hpp"
#include <cmath>

namespace otoge2019 {
  void Pacemaker::setScale(double scale)
  {
    this->scale = scale;
  }

  void Pacemaker::setTickFunction(std::function<double()> delegate)
  {
    getTick = delegate;
  }

  double Pacemaker::getAlicePosition()
  {
    return getPosition(getTick());
  }

  double Pacemaker::getPosition(double tick)
  {
    return tick * scale;
  }

  double Pacemaker::getSeconds(double position)
  {
    return position / scale;
  }

} // namespace otoge2019
