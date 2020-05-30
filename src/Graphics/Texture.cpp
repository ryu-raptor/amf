#include <iostream>
#include <ios>
#include "Graphics/Texture.hpp"

namespace Graphics {
  // 単にOpenGL上でのモデルオブジェクトを表す
  Texture::Texture(std::string path)
  {	  
    unsigned error = lodepng::decode(raw_data, width, height, path);
    if (error) {
      throw std::ios_base::failure(lodepng_error_text(error));
    }

    // make buffer
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &raw_data[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

#ifdef DEBUG    
    // dump
    for (int i = 0; i < raw_data.size(); i++) {
      std::cout << raw_data[i];
    }
    std::cout << std::endl;
#endif
  }

  Texture::~Texture()
  {
    // OpenGLリソースの解放
    glDeleteBuffers(1, &textureID);
  }

  void Texture::finalize()
  {
    // OpenGLリソースの解放
    glDeleteBuffers(1, &textureID);
  }

  GLuint Texture::getTexture() {
    return textureID;
  }

  unsigned int Texture::getHeight()
  {
    return height;
  }

  unsigned int Texture::getWidth()
  {
    return width;
  }
} // namespace Graphics
