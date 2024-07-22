#ifndef _NODE_H_
#define _NODE_H_

#include <string.h>
#include "tree.h"
#include "prop.h"

typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct _Node Node;

struct _Node {
  uint id;
  Prop* prop;
  T t;
};

#define t_new() { id_atomic++, NULL, NULL, NULL, NULL }

prop = p_new();
node->prop = prop;

typedef void (*n_call)(Node* node);

Node* n_add(Node* node, Node* pnode);
Node* n_new();

//Node* n_find();
//Node* n_add_prop();

Node* n_add(Node* node, Node* pnode) {
  if(pnode == NULL)
    return node;
  
  t_add(node->t, pnode->t);

  return node;
}

Node* n_new() {
  Node* new = (Node*)malloc(sizeof(Node));

  if(new == NULL) {
    fprintf(stderr, "n_new(), mem alloc failed\n");
    exit(-1);
  }
  
  memset(new, 0, sizeof(Node));
  t_new(&new->t);
  new->id = new->t.id;
    
  return new;
}

void t_init(t) {
  
}

Node* node = n_new();
node->prop = prop;

#endif /* _NODE_H_ */
