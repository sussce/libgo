#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct _Board Board;

struct _Board {
  unsigned int board_size;
  int board[];
};

#endif /* _BOARD_H_ */
