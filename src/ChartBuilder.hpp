#pragma once
#include <string>
#include <memory>
#include "Pacemaker.hpp"
#include "Chart.hpp"

namespace otoge2019 {
  class ChartBuilder {
    private:
      std::shared_ptr<Chart> chart;

    public:
      ChartBuilder(std::string, Pacemaker&);
      /// @fn
      /// Chartをビルドする
      void build(std::string chartpath, Pacemaker&);

      /// @fn
      /// 構築したものを返す
      std::shared_ptr<Chart> get();
  };
} // namespace otoge2019
