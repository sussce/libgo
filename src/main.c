/* This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdio.h>
#include "sgf_tree.h"

typedef void (*func)();

void n_seq_value(Value* value, L* l, func f);
void n_seq_prop(Prop* prop, L* l, func f);
void n_seq_node();
void n_seq(Node* head, func f);

void print_value(Value* value) {
  /* printf("[%s]", value->value); */
}

void print_prop(Prop* prop) {
  /* printf("%s", prop->id); */
  /* n_seq_value(prop->value, &prop->value->l, print_value); */
}

void print_node(Node* node) {
  /* n_seq_prop(node->prop, &node->prop->l, print_prop); */
  /* printf("\n"); */
}

int main(int argc, char** argv) {
  char* file = argv[1];
  Node* root = NULL;
  
  root = gparse(file);
  node_print(root);
}
