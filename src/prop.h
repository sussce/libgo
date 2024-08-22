#ifndef __GM1_PROP_H__
#define __GM1_PROP_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#include <stdlib.h>

#include "tree.h"
#include "error.h"

typedef struct _gprop gprop;
typedef struct _gvalue gvalue;

struct _gvalue {
  char* value;
  L l;
};
struct _gprop {
  char* id;
  gvalue* value;
  uint tkn;
  ulong uid;
  L l;
};

gprop* prop_new() {
  gprop* new = malloc(sizeof(gprop));

  if(!new)
    gerror("prop_new(), out of memory\n", 0);

  new->id = NULL;
  new->value = NULL;
  new->tkn = 0;
  new->uid = 0;
  l_init(&new->l);

  return new;
}

gprop* prop_add(gprop* head, gprop* prop) {
  if(!head)
    return prop;

  l_add(&head->l, &prop->l);
  return prop;
}

#endif /* __GM1_PROP_H__ */
