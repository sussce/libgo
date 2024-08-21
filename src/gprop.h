#ifndef _G_PROP_H_
#define _G_PROP_H_

#include <stdlib.h>

#include "tree.h"
#include "gerror.h"

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

#endif /* _G_PROP_H_ */
