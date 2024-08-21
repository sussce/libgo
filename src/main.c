/* This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdio.h>
#include "libgo.h"

int point_pos(char* pos) {
  char i = toupper((int)pos[0]);
  char j = toupper((int)pos[1]);

  return POS(IND(i), IND(j));
}

int main(int argc, char** argv) {
  char* file = argv[1];
  gnode* root = NULL;
  gtree tree;

  root = gparse(file);
  tree.root = root;
  node_print(root);

  int pos = point_pos("cd");
  printf("%d\n", pos);
}
