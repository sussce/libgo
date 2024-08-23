#include <stdio.h>
#include <stdlib.h>

#include "libgo.h"

int main(int argc, char** argv) {
  if(argc < 2) {
    fprintf(stderr, "miss file path.\n");
    exit(-1);
  }
  
  char* file = argv[1];
  gnode* root;
  
  root = gparse(file);
  node_print(root);
}
