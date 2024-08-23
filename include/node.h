#ifndef __GM1_NODE_H__
#define __GM1_NODE_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#include "prop.h"
#include "tree.h"

typedef struct _gnode gnode;
typedef struct _gtree gtree;

struct _gnode {
  gprop* prop;
  T t;
};
struct _gtree {
  gnode* root;
  gnode* curr;
};

gnode* node_new();
gnode* node_add(gnode* head, gnode* node);
void node_print(gnode* head);

#endif /* __GM1_NODE_H__ */
