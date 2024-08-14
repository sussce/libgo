/* This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdio.h>
#include "sgf_tree.h"
#include <string.h>

int main(int argc, char** argv) {
  char* file = argv[1];
  Node* root = NULL;
  
  root = gparse(file);

  node_print(root);
}
