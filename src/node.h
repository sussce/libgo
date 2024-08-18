#ifndef _NODE_H_
#define _NODE_H_

#include "tree.h"
#include "prop.h"

#include <stddef.h>
#include <assert.h>

#define typeof_member(T, m)	typeof(((T*)0)->m)

#define __same_type(a, b) \
  __builtin_types_compatible_p(typeof(a), typeof(b))

#define container_of(ptr, type, member) ({ \
	void *__mptr = (void *)(ptr); \
	static_assert(__same_type(*(ptr), ((type *)0)->member) ||	\
		      __same_type(*(ptr), void), \
		      "pointer type mismatch in container_of()");	\
	((type *)(__mptr - offsetof(type, member))); })

typedef struct _Node Node;

struct _Node {
  Prop* prop;
  T t;
};

Node* node_new() {
  Node* new = malloc(sizeof(Node));

  if(!new) {
    fprintf(stderr, "node_new(), out of memory\n");
    exit(-1);
  }

  new->prop = NULL;
  t_init(&new->t);

  return new;
}

Node* node_add(Node* head, Node* node) {
  if(!head)
    return node;

  t_add(&head->t, &node->t);
  return node;
}

void node_print(Node* head) {
  if(!head)
    return;

  printf("node: %d\n", head->t.id);

  if(head->t.next)
    node_print(container_of(head->t.next, Node, t));
  if(head->t.sib)
    node_print(container_of(head->t.sib, Node, t));    
}
#endif /* _NODE_H_ */
