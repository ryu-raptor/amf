#include "Note.hpp"

namespace otoge2019 {
  void Note::setPutScoreCallback(std::function<void(Judge, GLfloat, GLfloat)> func)
  {
    putScore = func;
  }

  void Note::loadNoteGraphic(std::string resourcepath)
  {
    // 何もしない
  }

  std::function<void(Judge, GLfloat, GLfloat)> Note::putScore;
  double Note::judgeThreasholds = 0.2;
  GLfloat Note::laneHeightOffset = 2;
} // namespace otoge2019
