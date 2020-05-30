#include "Chart.hpp"
#include "Trace.hpp"
#include <memory>
#include <vector>

namespace otoge2019 {
  class EditorChart : public Chart
  {
    std::shared_ptr<std::vector<std::shared_ptr<Trace>>> etrace; //> 参照Traceを保持する
    public:
      void setTrace(std::shared_ptr<std::vector<std::shared_ptr<Trace>>>);

      /// トレースを取得する
      Trace getTrace(unsigned int index) override;

      /// Aliceにあったものと同一の実装
      /// まだ踏んでいなかったら-1, 通り越していたら配列のサイズと同一の値
      int getLatestTraceIndex(double seconds) override;

      /// トレースの大きさを取得
      virtual int getTracesSize() override;
  };
} // namespace otoge2019
