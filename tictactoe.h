#include <sstream>
#include <cstdint>
#include <iostream>

/* 
  000
  000
  000
*/

typedef uint16_t Bitboard;

enum Color {
  NO_COLOR, BLACK, WHITE, COLOR_NB = 3,
};

enum File {
  FILE_1, FILE_2, FILE_3, 
};

enum Rank {
  RANK_1, RANK_2, RANK_3,
};

enum Square {
  SQ_1, SQ_2, SQ_3,
  SQ_4, SQ_5, SQ_6,
  SQ_7, SQ_8, SQ_9,
  SQ_NB = 9,
};

enum EvalMask {
  RANK1_MASK = 0b111000000,
  RANK2_MASK = 0b000111000,
  RANK3_MASK = 0b000000111,
  FILE1_MASK = 0b100100100,
  FILE2_MASK = 0b010010010,
  FILE3_MASK = 0b001001001,
};

#define ENABLE_BASE_OPERATORS_ON(T)                                \
constexpr T operator+(T d1, T d2) { return T(int(d1) + int(d2)); } \
constexpr T operator-(T d1, T d2) { return T(int(d1) - int(d2)); } \
constexpr T operator-(T d) { return T(-int(d)); }                  \
inline T& operator+=(T& d1, T d2) { return d1 = d1 + d2; }         \
inline T& operator-=(T& d1, T d2) { return d1 = d1 - d2; }

#define ENABLE_INCR_OPERATORS_ON(T)                                \
inline T& operator++(T& d) { return d = T(int(d) + 1); }           \
inline T& operator--(T& d) { return d = T(int(d) - 1); }

ENABLE_BASE_OPERATORS_ON(Color)

ENABLE_INCR_OPERATORS_ON(Square)
ENABLE_INCR_OPERATORS_ON(File)
ENABLE_INCR_OPERATORS_ON(Rank)

#undef ENABLE_INCR_OPERATORS_ON
#undef ENABLE_BASE_OPERATORS_ON

class Position {
public:
  void do_move(Square sq);
  void undo_move(Square sq);
  int game_ply() const;
  bool empty(Square s) const;
  Color color_on(Square s) const;
  Color side_to_move() const;
  bool pos_is_ok() const;
private:
  int gamePly;
  Bitboard byColorBB[COLOR_NB + 1];
  Color board[SQ_NB]; 
  Color sideToMove;
};

extern std::ostream& operator<<(std::ostream& os, const Position& pos);

inline Color Position::side_to_move() const {
  return sideToMove;
}

inline bool Position::empty(Square s) const {
  return board[s] == NO_COLOR;
}

inline Color Position::color_on(Square s) const {
  return board[s];
}

inline Bitboard Position::colors() const {
  return byColorBB[COLOR_NB];
}

inline Bitboard Position::colors(Color c) const {
  return byColorBB[c];
}

inline int Position::game_ply() const {
  return gamePly;
}

constexpr Square make_square(File f, Rank r) {
  return Square((r * 3) + f);
}

bool win(const Position& pos); 