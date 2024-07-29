#include <stdio.h>
#include "./src/sgf_tree.h"

void print_value(Value* value) {
  printf("[%s]", value->v);
}

void print_prop(Prop* prop) {
  printf("%s", prop->id);
  n_seq_value(prop->value, &prop->value->l, print_value);
}

void print_node(Node* node) {
  n_seq_prop(node->prop, &node->prop->l, print_prop);
  printf("\n");
}

void print_t(T* t) {
  printf("%d", t->id);
}

enum {
  ff_m = 1
};
  
void x(int a) {
  printf("%d\n", a);
}

int main(int argc, char** argv) {
  char* order =
    " (;F F [\\[4\\]] S Z [\\(19\\) \\;sz]"
    ";B[aa]C[a1] ;W[bb]C[b1] (;B[cc]C[c1] ;W[dd]C[d1]) (;B[ee]C[e1] ;W[ff]C[f1]))";
  char** curr = &order;
 
  Node* root = t_parse(curr, NULL, in_root);

  n_seq(root, print_node);

  char* p = "ff";

  return 0;
}
