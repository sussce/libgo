#include <stdio.h>
#include "sgf_tree.h"
#include <string.h>

void xy(char** p) {
  *p = "ef";
}

void y(char** p) {
  char* ptr;

  if(*p == NULL) {
    ptr = malloc(10);
    *p = ptr;

    for(int i = 0; i < 3; i++)
      *ptr++ = 'a';
    *ptr = '\0';
  }
  else
    ptr = *p;
    
  xy(&ptr);
}

int main(int argc, char** argv) {
  char* file = argv[1];
  Node* root = NULL;
  
  root = gparse(file);

  node_print(root);
}
