#pragma once
#include "Tap.hpp"

#include <memory>
#include "Note.hpp"
#include "Trace.hpp"
#include "ResourceFiler.hpp"
#include "Graphics/g3d/Panel.hpp"
#include "Graphics/g3d/DuplicatedPanel.hpp"

namespace otoge2019 {
  class EditorTap : public Tap {
    private:
      std::weak_ptr<Trace> etrace; //> Editorのe
      int sign;
      double eheight;

      void resetPosition();
    public:
      EditorTap(ButtonIdentifier, std::weak_ptr<Trace> trace);
      Result state(KeyBuffer::KeyState, double seconds) override;
      double metric(double seconds) override;

      /// EditorTapにしかないのでアップキャストが必須
      /// @fn
      /// トレースを持っているか
      bool hasTrace(std::shared_ptr<Trace>);

      /// EditorTapにしかないのでアップキャストが必須
      /// @fn
      /// ButtonIdentifierを確認
      bool doesBelong(ButtonIdentifier);

      /// EditorTapにしかないのでアップキャストが必須
      /// @fn
      /// ButtonIdentifierを確認
      ButtonIdentifier getButtonIdentifier();

      /// EditorTapにしかないのでアップキャストが必須
      /// @fn
      /// 持っているトレースを取得
      std::shared_ptr<Trace> getTrace();

      void render() override;
  };
} // namespace otoge2019
