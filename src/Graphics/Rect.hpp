#include "Graphics/glHeaders.hpp"

namespace Graphics {
  struct Rect
  {
    GLfloat width;
    GLfloat height;
    GLfloat x;
    GLfloat y;

    Rect(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
    {
      this->width  = width;
      this->height = height;
      this->x      = x;
      this->y      = y;
    }
  };
} // namespace Graphics
