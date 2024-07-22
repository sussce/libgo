#include <stdio.h>
#include "./src/node.h"
#include "./src/sgf_tree.h"
#include "./src/predef.h"

int main(int argc, char** argv) {
  char* order =
    " (;F F [\\[4\\]] S Z [\\(19\\) \\;sz]"
    ";B[aa]C[a1] ;W[bb]C[b1] (;B[cc]C[c1] ;W[dd]C[d1]) (;B[ee]C[e1] ;W[ff]C[f1]))";
  char** curr = &order;
 
  Node* root = t_parse(curr, NULL, in_root);

  return 0;
}
