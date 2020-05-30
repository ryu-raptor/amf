#ifndef Mook_cpp
#define Mook_cpp

// モック作成用フレーム
// 関数などを登録することで描画をテストするライブラリ
// まあGLUTみたいなものです

#include "Mook.hpp"
#include "Graphics/glHeaders.hpp"
#define GLOBAL_MASTER
#include "globals.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include "KeyBuffer.hpp"
#include <chrono>
#include "Singletons.hpp"

namespace otoge2019 {
namespace Mook {
  bool depthTest = true;
  std::string title = "Alice's Music Flight";

#ifndef OLDGL
  void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
  {
    // Print, log, whatever based on the enums and message
    puts(message);
  }
#endif

  std::function<void(int, int, int, int)> keyCallbackFunction;
  /// キー入力のコールバックを設定する(一度に一つだけ)
  void setKeyCallback(std::function<void(int, int, int, int)> handler)
  {
    keyCallbackFunction = handler;
  }

  /// std::functionはコールバックとして直接設定できないので, そのラッパー関数
  void keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if (keyCallbackFunction) {
      keyCallbackFunction(key, scancode, action, mods);
    }
  }

  std::function<void(void)> renderFunc;
  bool exitFlag = false;
  GLFWwindow* window;
  GLuint vertexArrayID;

  double fps()
  {
    static auto count = 1;
    static double FPS = 0;
    static auto begin = std::chrono::system_clock::now();
    if (count >= 60) {
      auto end = std::chrono::system_clock::now();
      double dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0;
      begin = std::chrono::system_clock::now();
      FPS = count / dur;
      std::cout << FPS << "\n";
      count = 1;
    }
    else {
      count++;
    }
    return FPS;
  }

  // Initialize with glfw
  int init()
  {
    puts("Init began");
    glewExperimental = true;
    if (!glfwInit()) {
      perror("GLFW init");
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
#ifdef OLDGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // openGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // to make macos happy;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want the old opengl    
#endif

    // Open a window and create its opengl context
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), NULL, NULL);
    if (window == NULL) {
      fprintf(stderr, "Window creation, may be opengl 3.3 not compatible\n");
      glfwTerminate();
      return -1;
    }
    glfwMakeContextCurrent(window); // initialize glew
    glfwSwapInterval(1);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
      perror("GLEW");
    }

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#ifndef OLDGL
      glDebugMessageCallback(debugMessage, NULL);
#endif
      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }
    else {
      puts("No debug feature available.");
    }

    // ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    if (depthTest) {
      // enable depth test
      glEnable(GL_DEPTH_TEST);
      // accept fragment if it close to the camera than the former one
      glDepthFunc(GL_LESS);
    }

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // キー入力のコールバック関数
    glfwSetKeyCallback(window, keyCallbackWrapper);
    // ラッパー関数の登録
    // Mookにキーバッファを設定
    setKeyCallback([&] (int keycode, int scancode, int action, int mod) {
      Singletons::keyBuffer.keyUpdate(keycode, action);
    });

    puts("Inits finished");

    return 0;
  }

  void setRenderProcess(std::function<void(void)> fp)
  {
    renderFunc = fp;
  }

  void doRenderProcess()
  {
    do {
      //std::cout << fps() << std::endl;
      glfwPollEvents();
      Singletons::keyBuffer.update();
      //fps();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      renderFunc();

      glfwSwapBuffers(window);
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 && !exitFlag);
	puts("exit rendering process");
  }

  void stopRenderProcess()
  {
    exitFlag = true;
  }

  // 終了処理
  void finalize()
  {
    puts("begun finalize");
    glDeleteVertexArrays(1, &vertexArrayID);

    glfwTerminate();
  }
} // namespace Mook
} // namespace otoge2019

#endif /* end of include guard */
