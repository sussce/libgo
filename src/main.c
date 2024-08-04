#include <stdio.h>

#include "sgf.h"
#include "token.h"

int main() {
  char* id = "W";
  int type = move;
  uint tkn = tkn_gen(id, type);
  
  printf("%s, 0x%x\n", id, tkn);
}
