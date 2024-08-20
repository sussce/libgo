#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct _Board Board;

struct _Board {
  int sz;
  uchar board[];
};

#endif /* _BOARD_H_ */
