#pragma once

#include <vector>
#include "Tap.hpp"
#include "Trace.hpp"

namespace otoge2019 {
  class Press : public Note
  {
    private:
      std::vector<Trace> traces;
      
    public:
      Press(ButtonIdentifier, std::vector<Trace> traces);
      Result state(KeyBuffer::KeyState, double seconds);
      double metric(double seconds);

      void render();

      static void loadNoteGraphic(std::string resourcepath);
      bool isFinished();
      // クロージャによって動的に生成された関数を実行する
      void scheduledTask();
  };
} // namespace otoge2019
