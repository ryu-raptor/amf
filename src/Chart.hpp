#pragma once

#include <vector>
#include <memory>
#include "KeyBuffer.hpp"
#include "Note.hpp"
#include "Trace.hpp"

namespace otoge2019 {
  class Chart
  {
    public:
      /// 添字へのアクセスはボタン識別子にて
      struct ButtonBuffer
      {
        private:
          KeyBuffer::KeyState states[2];

        public:
          KeyBuffer::KeyState get(ButtonIdentifier);
          void set(ButtonIdentifier, KeyBuffer::KeyState);
      };
    private:
      /// 内部処理をまとめたもの
      void check(ButtonBuffer, ButtonIdentifier, double seconds);
    public:
      std::shared_ptr<std::vector<std::shared_ptr<Note>>> notes[2]; // ButtonIdentifierでインデックスする
      std::shared_ptr<std::vector<std::shared_ptr<Note>>> finalizeVector;
      std::shared_ptr<std::vector<Trace>> traces;

      Chart();
      /// @fn
      /// 毎フレーム呼ばれるべき
      /// 描画とcheckStateが呼ばれる
      /// ButtonBufferもともすれば使われる
      void routine();
      
      /// 譜面を整理する
      void checkState(ButtonBuffer, double seconds);
      /// ファイナライズ対象のノーツを処理する
      void finalizer();
      /// トレースを取得する
      virtual Trace getTrace(unsigned int index);

      /// トレースの大きさを取得
      virtual int getTracesSize();

      /// Aliceにあったものと同一の実装
      /// まだ踏んでいなかったら-1, 通り越していたら配列のサイズと同一の値
      virtual int getLatestTraceIndex(double seconds);

      /// checkにあったものと同一
      /// Note::metric関数の返す値が最小のものを選ぶ
      int getLatestNoteIndex(ButtonIdentifier bi, double seconds);

      /// 新しい関数
      /// 与えられた秒数に対して最も小さいメトリックを持つものをイテレータとして返す.
      std::vector<std::shared_ptr<Note>>::iterator getMetricallyMinimumNote(ButtonIdentifier bi, double seconds);
  };
} // namespace otoge2019
