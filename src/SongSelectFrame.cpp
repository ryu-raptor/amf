#include "Frame.hpp"
#include "ResourceFiler.hpp"
#include "Singletons.hpp"
#include "Graphics/g2d/Image.hpp"
#include "Graphics/g2d/ImageShader.hpp"
#include "Graphics/glHeaders.hpp"
#include "KeyBuffer.hpp"
#include "GameFrame.hpp"
#include <memory>
#include <regex>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <ios>

using namespace Graphics::g2d;

namespace otoge2019 {
  class SongSelectFrame : public Frame {
    private:
      std::unique_ptr<ResourceFiler> rf;
      std::vector<std::string> chartpaths;
      int index;
      int size;

      std::unique_ptr<Image> bg;
      std::unique_ptr<ImageShader> shader;
      std::vector<std::unique_ptr<Image>> bgs;
    public:
      SongSelectFrame(std::string);
      void prepare();
      void routine();
  };

  SongSelectFrame::SongSelectFrame(std::string homepath) {
    rf.reset(new ResourceFiler(homepath));
    shader.reset(new ImageShader("resources/shaders/g2dShader.vertex.shader", "resources/shaders/g2dShader.fragment.shader"));
    bg.reset(new Image("fallback.png", -1, 1));
  }

  void SongSelectFrame::prepare()
  {
    // ディレクトリ情報を取得
    auto chartdir = rf->get("Chart", "ChartDirectory");
    std::regex chartfile_pattern(R"(.+\.chart$)");
    DIR* dir;
    struct dirent* dp;
    struct stat buf;
    if ((dir = opendir(chartdir.c_str())) == NULL)
    {
      perror("ディレクトリオープン");
      throw std::ios_base::failure("ディレクトリが不正です");
    }
    for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
      auto fname = std::string(dp->d_name);
      if (std::regex_match(fname, chartfile_pattern)) {
        chartpaths.push_back(chartdir + "/" + fname);
      }
    }

    closedir(dir);

    size = chartpaths.size();
    index = 0;

    for (auto chartp : chartpaths) {
      bgs.push_back(std::move(std::unique_ptr<Image>(new Image(chartp + "/bg.png", -1, 0.5))));
    }
  }

  void SongSelectFrame::routine()
  {
    if (Singletons::keyBuffer.getState(KeyConfigurator::Key::down) == KeyBuffer::KeyState::hit) {
      index = (index + 1) % size;
    }
    else if (Singletons::keyBuffer.getState(KeyConfigurator::Key::up) == KeyBuffer::KeyState::hit) {
      index = (index - 1 < 0) ? size - 1 : index - 1;
    }
    if (Singletons::keyBuffer.getState(KeyConfigurator::Key::select) == KeyBuffer::KeyState::hit) {
      // 選択した譜面でインスタンス化
      frameController->segue(std::shared_ptr<Frame>(new GameFrame(10.0, chartpaths.at(index))));
    }

    shader->render(bgs.at(index).get());
  }
} // namespace otoge2019
