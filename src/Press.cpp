#include <cmath>
#include "Press.hpp"
#include "Exceptions.hpp"

namespace otoge2019 {
  Press::Press(ButtonIdentifier bi, std::vector<Trace> traces)
  {
    if (traces.size() < 2) {
      throw LogicalError();
    }

    this->traces = traces;
  }

  Press::Result Press::state(KeyBuffer::KeyState ks, double seconds)
  {
    return Result::release;
  }
  
  double Press::metric(double seconds)
  {
    // Judge.md参照
    // Xより前にいるか
    // tracesはサイズが2以上だと保証されている(コンストラクタが保証する)
    if (seconds <= (*traces.begin()).seconds) {
      return std::abs(seconds - (*traces.begin()).seconds);
    }
    // Zより前にいるか(Xより後ろなのは確認済みなので)
    else if (seconds <= (*(traces.end() - 1)).seconds) {
      return 0;
    }
    // Zより後ろ
    else {
      return std::abs(seconds - (*(traces.end() - 1)).seconds);
    }
  }

  bool Press::isFinished()
  {
    return true;
  }

  // クロージャによって動的に生成された関数を実行する
  void Press::scheduledTask()
  {
  }

  void Press::render()
  {
  }
} // namespace otoge2019
