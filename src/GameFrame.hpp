#pragma once
#include <memory>
#include <string>
#include "Graphics/g2d/Image.hpp"
#include "Graphics/g2d/ImageShader.hpp"
#include "KeyBuffer.hpp"
#include "Alice.hpp"
#include "Pacemaker.hpp"
#include "SFML/Audio.hpp"
#include "Graphics/g3d/Line.hpp"
#include "TraceRenderer.hpp"
#include "ResourceFiler.hpp"
#include "Effector.hpp"
#include "Nice.hpp"
#include "Bad.hpp"
#include "Sky.hpp"
#include "Frame.hpp"
#include "KeyConfigurator.hpp"

namespace otoge2019 {
  /// ゲームに関する諸々を詰め込んどくばしょ
  /// Pacemaker, Chart, Music, Alice, BG, Effect, KeyBuffer
  /// Noteとトレースのデフォルトグラフィックはすでに設定してあるとする
  class GameFrame : public Frame {
    private:
      Pacemaker pacemaker;
      std::string chartpath;
      std::shared_ptr<Chart> chart;
      std::shared_ptr<Alice> alice;
      std::unique_ptr<TraceRenderer> traceRenderer;
      sf::Music music;
      Graphics::g3d::Line line;
      Sky sky;
      std::unique_ptr<Graphics::g2d::ImageShader> imageShader;
      std::unique_ptr<Graphics::g2d::Image> guage;
      KeyConfigurator keyConfig;

      Effector effector;

      /// put_scoreに登録してエフェクトを発生させる
      void test_put_effect(Judge, GLfloat, GLfloat);

    public:
      GameFrame(double scale, std::string chartpath);
      /// @fn
      /// 準備をする
      /// Chart, Music, Alice, KeyBuffer, BG, (Effect)を準備
      void prepare() override;
      /// @fn
      /// 毎フレーム呼ばれる
      void routine() override;

      void show() override;
      void dismiss() override;
  };
}

