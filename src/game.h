#ifndef __GM1_GAME_H__
#define __GM1_GAME_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILATION)
#error "only libgo.h can be included directly."
#endif

#include "node.h"

typedef struct _ggame ggame;
typedef struct _gheader gheader;

struct _gheader {
  char* ru;
  float km;
  int ha;
  char* re;
  char* pb;
  char* pw;
  char* br;
  char* wr;
  char* gn;
  char* dt;
  int sz;  
};
struct _ggame {
  gheader* header;
  gtree* tree;

  int turn;
  int ko;
  int mn;
};

#endif /* __GM1_GAME_H__ */
