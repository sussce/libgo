#ifndef __GM1_ERROR_H__
#define __GM1_ERROR_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#include <stdlib.h>

void gerror(const char* msg, int arg) {
  fprintf(stderr, msg, arg);
  exit(-1);
}

void gassert(int cond, const char* msg, int arg) {
  if(!cond)
    gerror(msg, arg);
}

#endif /* __GM1_ERROR_H__ */
