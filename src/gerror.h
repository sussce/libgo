#ifndef _G_ERROR_H_
#define _G_ERROR_H_

#include <stdlib.h>

void gerror(const char* msg, int arg) {
  fprintf(stderr, msg, arg);
  exit(-1);
}

void gassert(int cond, const char* msg, int arg) {
  if(!cond)
    gerror(msg, arg);
}

#endif /* _G_ERROR_H_ */
