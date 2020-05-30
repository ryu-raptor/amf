#include "EditorTraceBuilder.hpp"
#include <iostream>
#include <sstream>
#include <ios>

namespace otoge2019 {
  std::shared_ptr<std::vector<std::shared_ptr<Trace>>> EditorTraceBuilder::build(std::string tracefile, Pacemaker &pacemaker)
  {
    std::ifstream stream(tracefile);
    std::shared_ptr<std::vector<std::shared_ptr<Trace>>> v(new std::vector<std::shared_ptr<Trace>>());
    if (stream.fail()) {
      throw std::ios_base::failure("TraceBuiler: トレースファイルのオープンに失敗しました");
    }

    std::string line;
    while (std::getline(stream, line)) {
      double t, h;
      std::stringstream ss(line);
      ss >> t >> h;
      std::cout << "t: " << t << ", h: " << h << "\n";
      std::shared_ptr<Trace> trace(new Trace());
      trace->seconds = t;
      trace->height = h;
      trace->position = pacemaker.getPosition(t);
      v->push_back(trace);
    }

    stream.close();
    return v;
  }
} // namespace otoge2019
