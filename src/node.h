#ifndef __GM1_NODE_H__
#define __GM1_NODE_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILATION)
#error "Only "libgo.h" can be included directly."
#endif

#include <stdlib.h>

#include "tree.h"
#include "error.h"
#include "prop.h"

typedef struct _gnode gnode;

struct _gnode {
  gprop* prop;
  T t;
};

gnode* node_new() {
  gnode* new = malloc(sizeof(gnode));

  if(!new)
    gerror("node_new(), out of memory\n", 0);

  new->prop = NULL;
  t_init(&new->t);

  return new;
}

gnode* node_add(gnode* head, gnode* node) {
  if(!head)
    return node;

  t_add(&head->t, &node->t);
  return node;
}

void node_print(gnode* head) {
  if(!head)
    return;

  printf("node: %d\n", head->t.id);

  if(head->t.next)
    node_print(container_of(head->t.next, gnode, t));
  if(head->t.sib)
    node_print(container_of(head->t.sib, gnode, t));    
}

#endif /* __GM1_NODE_H__ */
