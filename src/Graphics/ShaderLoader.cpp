#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint bindShader();

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
  // create shaders
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // read the vertex shader code from the file
  std::string vertexShaderCode;
  std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
  if (vertexShaderStream.is_open()) {
	std::stringstream sstr;
	sstr << vertexShaderStream.rdbuf();
	vertexShaderCode = sstr.str();
	vertexShaderStream.close();
  }
  else {
	std::cout << "Impossible to open" << std::endl;
	getchar();
        throw std::ios_base::failure("頂点シェーダのオープンに失敗");
  }

  // read the fragment shader code from the file
  std::string fragmentShaderCode;
  std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
  if (fragmentShaderStream.is_open()) {
	std::stringstream sstr;
	sstr << fragmentShaderStream.rdbuf();
	fragmentShaderCode = sstr.str();
	fragmentShaderStream.close();
  }
  else {
	std::cout << "Impossible to open" << std::endl;
	getchar();
        throw std::ios_base::failure("フラグメントシェーダのオープンに失敗");
  }

  GLint result = GL_FALSE;
  int infoLogLength;

  // compile vertex shader
  char const* vertexSourcePointer = vertexShaderCode.c_str();
  glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
  glCompileShader(vertexShaderID);

  // check vertex shader
  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
	std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
	glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
	std::cout << &vertexShaderErrorMessage[0] << std::endl;
  }

  // compile fragment shader
  char const* fragmentSourcePointer = fragmentShaderCode.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
  glCompileShader(fragmentShaderID);

  // check fragment shader
  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
	std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
	glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
	std::cout << &fragmentShaderErrorMessage[0] << std::endl;
  }

  // link the program
  GLuint programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  // check the program
  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

  if (infoLogLength > 0) {
	std::vector<char> programErrorMessage(infoLogLength + 1);
	glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
	std::cout << &programErrorMessage[0] << std::endl;
  }

  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  return programID;
}
