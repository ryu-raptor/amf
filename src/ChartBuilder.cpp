#include "ChartBuilder.hpp"
#include "TraceBuilder.hpp"
#include "NoteBuilder.hpp"

namespace otoge2019 {
  ChartBuilder::ChartBuilder(std::string chartpath, Pacemaker& pacemaker)
  {
    build(chartpath, pacemaker);
  }

  void ChartBuilder::build(std::string chartpath, Pacemaker& pacemaker)
  {
    chart.reset(new Chart());
    auto notepath = chartpath + "/" + "note";
    auto tracepath = chartpath + "/" + "trace";

    TraceBuilder tbuilder;
    NoteBuilder nbuilder;
    chart->traces = tbuilder.build(tracepath, pacemaker);
    nbuilder.build(notepath, chart->traces);
    chart->notes[ButtonIdentifier::Upper] = nbuilder.get(ButtonIdentifier::Upper);
    chart->notes[ButtonIdentifier::Lower] = nbuilder.get(ButtonIdentifier::Lower);
  }
  std::shared_ptr<Chart> ChartBuilder::get()
  {
    return chart;
  }
} // namespace otoge2019
