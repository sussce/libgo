#ifndef _NODE_H_
#define _NODE_H_

#include "prop.h"
#include "tree.h"

typedef struct _Node Node;

struct _Node {
  int id;
  Prop* prop;

  T* t;
};

Node* n_new() {
  Node* new = malloc(sizeof(Node));
  return new;
}

#endif /* _NODE_H_ */
