#pragma once
#include <vector>
#include <memory>
#include "ButtonIdentifier.hpp"
#include "Trace.hpp"
#include "Note.hpp"

namespace otoge2019 {
  /// トレースを用いてノーツを生成する.
  class EditorNoteBuilder
  {
    private:
      enum class NoteType
      {
        tap, press
      };

      std::shared_ptr<std::vector<std::shared_ptr<Trace>>> traces;
      std::shared_ptr<std::vector<std::shared_ptr<Note>>> notes;

      /// @fn
      /// ノーツを作成
      std::shared_ptr<Note> factory(ButtonIdentifier, NoteType, std::vector<int>);
    public:
      class InvalidFormat
      {
      };

      /// @fn
      /// ノーツをビルド
      void build(std::string, std::shared_ptr<std::vector<std::shared_ptr<Trace>>>);
      std::shared_ptr<std::vector<std::shared_ptr<Note>>> get();
  };
} // namespace otoge2019
