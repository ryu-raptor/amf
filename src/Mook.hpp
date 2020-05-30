#pragma once
#include "Graphics/glHeaders.hpp"
#include <functional>
#include "KeyBuffer.hpp"

namespace otoge2019 {
namespace Mook {
#ifndef OLDGL
  void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
#endif

  extern std::function<void(int, int, int, int)> keyCallbackFunction;
  /// キー入力のコールバックを設定する(一度に一つだけ)
  void setKeyCallback(std::function<void(int, int, int, int)> handler);

  /// std::functionはコールバックとして直接設定できないので, そのラッパー関数
  void keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods);

  extern std::string title;
  extern KeyBuffer keyBuffer;
  extern bool depthTest; //> 深度テストを実施するか(デフォルトはtrue)
  extern std::function<void(void)> renderFunc;
  extern bool exitFlag;
  extern GLFWwindow* window;
  extern GLuint vertexArrayID;

  double fps();
  /// Initialize with glfw
  int init();
  void setRenderProcess(std::function<void(void)> fp);
  void doRenderProcess();
  void stopRenderProcess();
  /// 終了処理
  void finalize();
} // namespace Mook
} // namespace otoge2019
