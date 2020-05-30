#pragma once
#include "Graphics/glHeaders.hpp"
#include "Follower.hpp"

namespace otoge2019 {
  class Followee
  {
    public:
      /// 対象に自分を覚えてもらう
      virtual void followee(Follower*) = 0;
  };
} // namespace otoge2019
