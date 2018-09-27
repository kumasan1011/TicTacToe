/*
  tictactoe program
*/

#include "tictactoe.h"

namespace {

const std::string ColorToChar("-〇X");

const EvalMask EvalMaskArray[] = {
  RANK1_MASK,RANK2_MASK, RANK3_MASK, FILE1_MASK, FILE2_MASK, FILE3_MASK
};

const int WIN_BITS_NUM = 3;

}

/// operator<<(Position) returns an ASCII representation of the position

std::ostream& operator<<(std::ostream& os, const Position& pos) {

  os << "\n +---+---+---+\n";

  for (Rank r = RANK_1; r <= RANK_3; ++r)
  {
    for (File f = FILE_1; f <= FILE_3; ++f) {
      Color c = pos.color_on(make_square(f, r));
      os << " | " << ColorToChar[c];
    }
    os << " |\n +---+---+---+\n";
  }

  os << "\nColor: " << (pos.side_to_move() == WHITE ? "WHITE" : "BLACK");

  return os;
}

inline bool Position::pos_is_ok() const {
  return true;
}

// 自分が勝ちかを判定
bool win(const Position& pos) {

  Bitboard bb = pos.colors(pos.side_to_move());

  for (EvalMask em : EvalMaskArray) {
    if (__builtin_popcount(bb & em) == WIN_BITS_NUM)
      return true;     
  }

  return false;
} 