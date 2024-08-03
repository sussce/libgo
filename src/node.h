#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "predef.h"
#include "prop.h"
#include "tree.h"

typedef struct _Node Node;

struct _Node {
  uint id;
  Prop* prop;
  T t;
};

typedef void (*n_call)(Node* node);
typedef void (*n_prop_call)(Prop* prop);
typedef void (*n_value_call)(Value* value);

Node* n_add(Node* node, Node* pnode) {
  if(pnode == NULL)
    return node;
  
  t_add(&node->t, &pnode->t);

  return node;
}

Node* n_new() {
  Node* new = (Node*)malloc(sizeof(Node));

  if(new == NULL) {
    fprintf(stderr, "n_new(), mem alloc failed\n");
    exit(-1);
  }
  
  memset(new, 0, sizeof(Node));
  t_init(&new->t, -1);
  new->id = new->t.id;
    
  return new;
}

void n_seq_value(Value* value, L* head, n_value_call call) {
  call(value);

  if(value->l.next != head)
    n_seq_value(t_ptr(value->l.next, Value, l), head, call);
}

void n_seq_prop(Prop* prop, L* head, n_prop_call call) {
  call(prop);
 
  if(prop->l.next != head)
    n_seq_prop(t_ptr(prop->l.next, Prop, l), head, call);
}

void n_seq(Node* node, n_call call) {
  call(node);
  
  if(node->t.next)
    n_seq(t_ptr(node->t.next, Node, t), call);
  if(node->t.next_sib)
    n_seq(t_ptr(node->t.next_sib, Node, t), call);
}

#endif /* _NODE_H_ */
