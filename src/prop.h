#ifndef _PROP_H_
#define _PROP_H_

#include "tree.h"

typedef struct _Prop Prop;

struct _Prop {
  char* id;
  value* v;

  /* char** v; */
  /* unsigned int nv; */

  unsigned int token;
  unsigned long uid;
  L* l;
};

//prop_find(Prop* prop, );

Prop* n_prop_new() {
  Prop* new = malloc(sizeof(Prop));
  return new;
}

#endif /* _PROP_H_ */
