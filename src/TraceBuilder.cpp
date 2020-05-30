#include "TraceBuilder.hpp"
#include <ios>

namespace otoge2019 {
  std::shared_ptr<std::vector<Trace>> TraceBuilder::build(std::string tracefile, Pacemaker &pacemaker)
  {
    std::ifstream stream(tracefile);
    std::shared_ptr<std::vector<Trace>> v(new std::vector<Trace>());
    if (stream.fail()) {
      throw std::ios_base::failure("TraceBuiler: トレースファイルのオープンに失敗しました");
    }

    while (!stream.eof()) {
      double t, h;
      stream >> t >> h;
      Trace trace;
      trace.seconds = t;
      trace.height = h;
      trace.position = pacemaker.getPosition(t);
      v->push_back(trace);
    }

    stream.close();
    return v;
  }
} // namespace otoge2019
