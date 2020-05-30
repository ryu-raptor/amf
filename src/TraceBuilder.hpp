#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Trace.hpp"
#include "Pacemaker.hpp"

namespace otoge2019 {
  /// ファイルからトレースを作成
  class TraceBuilder
  {
    public:
      /// @fn
      /// トレースをビルド
      std::shared_ptr<std::vector<Trace>> build(std::string, Pacemaker&);
  };
} // namespace otoge2019
