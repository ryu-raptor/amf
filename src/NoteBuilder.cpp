#include "NoteBuilder.hpp"
#include "Tap.hpp"
#include "Press.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <ios>

namespace otoge2019 {
  std::shared_ptr<Note> NoteBuilder::factory(ButtonIdentifier bi, NoteType type, std::vector<int> args)
  {
    switch (type) {
      case NoteType::tap:
        if (args.size() >= 1) {
          auto trace = traces->at(args[0]);
          return std::shared_ptr<Note>(new Tap(bi, trace));
        }
        break;
      case NoteType::press:
        std::vector<Trace> v;
        if (args.size() >= 2) {
          for (auto i : args) {
            v.push_back(traces->at(i));
          }
          return std::shared_ptr<Note>(new Press(bi, v));
        }
        break;
    }
    throw InvalidFormat();
  }

  void NoteBuilder::build(std::string notefile, std::shared_ptr<std::vector<Trace>> traces)
  {
    std::ifstream stream(notefile);
    notes[0].reset(new std::vector<std::shared_ptr<Note>>());
    notes[1].reset(new std::vector<std::shared_ptr<Note>>());
    if (stream.fail()) {
      throw std::ios_base::failure("NoteBuiler: ノーツファイルのオープンに失敗しました");
    }

    // copy pointer
    this->traces = traces;

    std::string line;
    while (std::getline(stream, line)) {
      std::stringstream ss;
      ss << line;
      int buttonIdIndex, noteType;
      ss >> buttonIdIndex >> noteType;
      ButtonIdentifier bi;
      NoteType type;
      switch (buttonIdIndex) {
        case 0:
          bi = ButtonIdentifier::Upper;
          break;
        case 1:
          bi = ButtonIdentifier::Lower;
          break;
        default:
          throw InvalidFormat();
      }

      switch (noteType) {
        case 0:
          type = NoteType::tap;
          break;
        case 1:
          type = NoteType::press;
          break;
        default:
          throw InvalidFormat();
      }

      std::vector<int> args;
      while (!ss.eof()) {
        int a;
        ss >> a;
        args.push_back(a);
      }
      // ファクトリでインスタンス化
      auto note = factory(bi, type, args);
      notes[bi]->push_back(note);
    }
    for (int bi = 0; bi < 2; bi++) {
      // ソート(メトリックで)
      std::sort(notes[bi]->begin(), notes[bi]->end(),
                [](std::shared_ptr<Note> x, std::shared_ptr<Note> y) {
                  return x->metric(0) < y->metric(0);
                }
               );
    }

    stream.close();
  }

  std::shared_ptr<std::vector<std::shared_ptr<Note>>> NoteBuilder::get(ButtonIdentifier bi)
  {
    return notes[bi];
  }
} // namespace otoge2019
