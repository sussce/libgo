#ifndef _PROP_H_
#define _PROP_H_

#include <stdlib.h>

#include "tree.h"

typedef struct _Prop Prop;
typedef struct _Value Value;

struct _Value {
  char* value;
  L l;
};
struct _Prop {
  char* id;
  Value* value;
  uint tkn;
  ulong uid;
  L l;
};

Prop* prop_new() {
  Prop* new = malloc(sizeof(Prop));

  if(!new) {
    fprintf(stderr, "prop_new(), out of memory\n");
    exit(-1);
  }

  new->id = NULL;
  new->value = NULL;
  new->tkn = 0;
  new->uid = 0;
  l_init(&new->l);

  return new;
}

Prop* prop_add(Prop* head, Prop* prop) {
  if(!head)
    return prop;

  l_add(&head->l, &prop->l);
  return prop;
}

#endif /* _PROP_H_ */
