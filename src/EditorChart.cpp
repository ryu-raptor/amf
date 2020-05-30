#include "EditorChart.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace otoge2019 {
  void EditorChart::setTrace(std::shared_ptr<std::vector<std::shared_ptr<Trace>>> tp)
  {
    etrace = tp;
  }

  /// トレースを取得する
  Trace EditorChart::getTrace(unsigned int index)
  {
    // ポインタを取得してデレファレンスしてインターフェースを合わせる
    auto traceu = *((etrace->at(index)).get());
    return traceu;
  }

  /// Aliceにあったものと同一の実装
  /// まだ踏んでいなかったら-1, 通り越していたら配列のサイズと同一の値
  int EditorChart::getLatestTraceIndex(double seconds)
  {
    int index = -1;
    int i;
    for (i = 0; i < etrace->size(); i++) {
      if ((*etrace)[i]->seconds > seconds)
      {
        break;
      }
    }
    index = i - 1;
    return index;
  }

  int EditorChart::getTracesSize()
  {
    return etrace->size();
  }
} // namespace otoge2019
