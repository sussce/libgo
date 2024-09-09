#ifndef __GM1_PROP_H__
#define __GM1_PROP_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#include "tree.h"

typedef struct _gprop gprop;
typedef struct _gvalue gvalue;

struct _gprop {
  char* id;
  gvalue* value;
  uint tkn;
  ulong uid;
  L l;
};
struct _gvalue {
  char* value;
  L l;
};

gvalue* value_new();
gvalue* value_add(gvalue* head, gvalue* value);
gprop* prop_new();
gprop* prop_add(gprop* head, gprop* prop);

#endif /* __GM1_PROP_H__ */
