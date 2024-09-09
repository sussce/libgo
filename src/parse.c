#include "parse.h"
#include "node.h"
#include "prop.h"
#include "error.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UcLetter 0xfe
#define is_char(c) ((ch) == (c))
#define step() ((ch) = getc(fp))

static FILE* fp;
static int ch;

static inline void step_n() {
  for(;;) {
    step();    
    if(!isspace((int)ch))
      break;
  }
}

static inline void match_only(char c) {
  if(c == (char)UcLetter)
    gassert(isupper((int)ch), "miss UcLetter\n", 0);
  else
    gassert(is_char(c), "miss %c\n", c);
}

static inline void match(char c) {
  match_only(c);
  step_n();
}

static void prop_ident(gprop** head) {
  match_only(UcLetter);

  char* id = malloc(256*sizeof(char));
  char* raw = id;
  
  for(;;) {
    if(is_char('['))
      break;
    if(isspace((int)ch)) {
      step_n();
      break;
    }
    if(!isupper((int)ch))
      gerror("miss UcLetter\n", 0);
      
    *raw++ = ch;
    step();
  }
  *raw = '\0';
  (*head)->id = id;
  
  match_only('[');
}

static void prop_value(gprop** head) {
  match('[');

  char *value = malloc(1024*sizeof(char)),
    *raw = value;
  
  for(;;) {
    if(is_char(']'))
      break;
    if(is_char('\\'))
      step();

    *raw++ =ch;
    step();
  }
  *raw = '\0';
  
  gvalue* dummy = value_new();  
  (*head)->value = value_add((*head)->value, dummy);
  (*head)->value->value = value;
  
  match(']');
}

void value_iter(gvalue* head) {
  gvalue* a = head;

  do {
    printf("[%s]", head->value);
    head = container_of(head->l.next, gvalue, l);
  } while(head != a);
}

static void property(gprop** head) {
  match_only(UcLetter);

  gprop* dummy = prop_new();
  *head = prop_add(*head, dummy);
 
  int list_t = 0;
  
  prop_ident(head);
  printf("%s", (*head)->id);
  
  if(strcmp((*head)->id, "AW") == 0 ||
     strcmp((*head)->id, "AB") == 0)
    list_t = 1;

  for(;;) {
    prop_value(head);

    // if((*head)->tkn && LIST)
    if(!list_t)
      break;
    if(!is_char('['))
      break;
  }
  value_iter((*head)->value);
}

static void node(gnode** head) {
  match(';');

  gnode* dummy = node_new();
  *head = node_add(*head, dummy);

  for(;;) {
    if(!isupper((int)ch))
      break;
    property(&(*head)->prop);
  }
}

static void sequence(gnode** head) {
  match_only(';');
    
  for(;;) {
    if(!is_char(';'))
      break;      
    node(head);
  }
}

#define save_ptr(p1, p2) \
  p1 = *p2; \
  p2 = &p1;

static void game_tree(gnode** head) {
  match('(');
  match_only(';');

  gnode* dummy;
  
  if(!*head)
    node(head);

  save_ptr(dummy, head);
  sequence(head);
  
  for(;;) {
    if(!is_char('('))
      break;
    game_tree(head);
  }
  
  match(')');
}

static void collection() {}

gnode* gparse(const char* filename) {
  gnode* root = NULL;
  
  fp = fopen(filename, "r");

  if(!fp)
    return NULL;

  step_n();
  game_tree(&root);
  
  fclose(fp);
  return root;
}
