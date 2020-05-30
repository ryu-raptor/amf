#pragma once

#include <string>
#include <vector>
#include "Graphics/lodepng/lodepng.h"
#include "Graphics/glHeaders.hpp"

namespace Graphics {
  class Texture {
    std::vector<unsigned char> raw_data;
    unsigned int width, height;

    GLuint textureID;
    public:
    Texture(std::string path);
    ~Texture();
    void finalize();
    GLuint getTexture();
    unsigned int getHeight();
    unsigned int getWidth();
  };
} // namespace Graphics
