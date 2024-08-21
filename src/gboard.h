#ifndef _G_BOARD_H_
#define _G_BOARD_H_

#include "ghash.h"

/*            A   B   C   D   E   F   G
     i   -1   0   1   2   3   4   5   6
  j +----------------------------------
     7|  64  65  66  67  68  69  70  71  72
G 7  6|  56  57  58  59  60  61  62  63   
F 6  5|  48  49  50  51  52  53  54  55   
E 5  4|  40  41  42  43  44  45  46  47   
D 4  3|  32  33  34  35  36  37  38  39
C 3  2|  24  25  26  27  28  29  30  31   
B 2  1|  16  17  18  19  20  21  22  23   
A 1  0|   8   9  10  11  12  13  14  15
    -1|   0   1   2   3   4   5   6   7

              A   B   C   D   E   F   G
     i   -1   0   1   2   3   4   5   6
  j +----------------------------------
     7|   #   #   #   #   #   #   #   #   #
G 7  6|   #   .   .   .   .   .   .   .
F 6  5|   #   .   .   .   .   .   .   .
E 5  4|   #   .   .   .   .   .   .   .
D 4  3|   #   .   .   .   .   .   .   .
C 3  2|   #   .   .   .   .   .   .   .
B 2  1|   #   .   .   .   .   .   .   .
A 1  0|   #   .   .   .   .   .   .   .
    -1|   #   #   #   #   #   #   #   #
*/

#define MIN_BOARD 1
#define MAX_BOARD 7
#define MAX_HA 9

#define BOARD_SIZE ((MAX_BOARD + 2) * (MAX_BOARD + 1) + 1)
#define BOARD_MIN (MAX_BOARD + 2)
#define BOARD_MAX (MAX_BOARD + 1) * (MAX_BOARD + 1)

#define POS(i, j) ((MAX_BOARD + 2) + (j) * (MAX_BOARD + 1) + (i))
#define DELTA(di, dj) ((di) * (MAX_BOARD + 1) + (dj))
#define I(pos) ((pos) % (MAX_BOARD + 1) - 1)
#define J(pos) ((pos) / (MAX_BOARD + 1) - 1)

#define NS (MAX_BOARD + 1)
#define WE 1
#define NORTH(pos) ((pos) - NS)
#define WEST(pos) ((pos) - 1)
#define SOUTH(pos) ((pos) + NS)
#define EAST(pos) ((pos) + 1)
#define NW(pos) ((pos) - NS - 1)
#define SW(pos) ((pos) + NS - 1)
#define SE(pos) ((pos) + NS + 1)
#define NE(pos) ((pos) - NS + 1)
#define NN(pos) ((pos) - 2 * NS)
#define WW(pos) ((pos) - 2)
#define SS(pos) ((pos) + 2 * NS)
#define EE(pos) ((pos) + 2)

#define DIRECT_NEIGHBORS(pos1, pos2)            \
  ((pos1) == SOUTH(pos2)                        \
   || (pos1) == WEST(pos2)                      \
   || (pos1) == NORTH(pos2)                     \
   || (pos1) == EAST(pos2))

#define DIAGONAL_NEIGHBORS(pos1, pos2)          \
  ((pos1) == SW(pos2)                           \
   || (pos1) == NW(pos2)                        \
   || (pos1) == NE(pos2)                        \
   || (pos1) == SE(pos2))

#define BOARD(i, j) board[POS(i, j)]
#define ON_BOARD(pos) (board[pos] != GRAY)
#define IND(c) (c - 0x11 - '0')

enum _colors {
  EMPTY,
  BLACK,
  WHITE,
  GREY
};

typedef struct _gboard gboard;

struct _gboard {
  int sz;
  uchar board[BOARD_SIZE];

  int cap_b;
  int cap_w;
};

#endif /* _G_BOARD_H_ */
