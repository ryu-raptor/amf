#pragma once
#include <vector>
#include <memory>
#include "ButtonIdentifier.hpp"
#include "Trace.hpp"
#include "Note.hpp"

namespace otoge2019 {
  /// トレースを用いてノーツを生成する.
  class NoteBuilder
  {
    private:
      enum class NoteType
      {
        tap, press
      };

      std::shared_ptr<std::vector<Trace>> traces;
      std::shared_ptr<std::vector<std::shared_ptr<Note>>> notes[2]; //> 保存しておく

      /// @fn
      /// ノーツを作成
      std::shared_ptr<Note> factory(ButtonIdentifier, NoteType, std::vector<int>);
    public:
      class InvalidFormat
      {
      };

      /// @fn
      /// ノーツをビルド
      void build(std::string, std::shared_ptr<std::vector<Trace>>);
      std::shared_ptr<std::vector<std::shared_ptr<Note>>> get(ButtonIdentifier);
  };
} // namespace otoge2019
