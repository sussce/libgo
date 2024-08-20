#ifndef _PARSE_H_
#define _PARSE_H_

#include <stdlib.h>
#include <ctype.h>

#include "tree.h"
#include "node.h"
#include "prop.h"

#define UcLetter 0xfe
#define is_char(c) ((ch) == (c))
#define step() ((ch) = getc(fp))

typedef struct _gtree gtree;

struct _gtree {
  Node* root;
  Node* curr;
};

static FILE* fp;
static int ch;

void gerror(const char* msg, int arg) {
  fprintf(stderr, msg, arg);
  exit(-1);
}

void gassert(int cond, const char* msg, int arg) {
  if(!cond)
    gerror(msg, arg);
}

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

static void prop_ident(Prop** head) {
  match_only(UcLetter);

  char* id = malloc(256*sizeof(char));
  char* raw = id;
  
  for(;;) {
    if(!is_char('[') && !isupper((int)ch))
      gerror("miss UcLetter\n", 0);
    if(is_char('['))
      break;

    *raw++ = ch;
    step();
  }
  *raw = '\0';
  
  match_only('[');
}

static void prop_value(Prop** head) {
  match('[');

  char* value = malloc(1024*sizeof(char));
  char* p = value;
  
  for(;;) {
    if(is_char(']'))
      break;
    if(is_char('\\'))
      step();
    step();
  }

  match(']');
}

static void property(Prop** head) {
  match_only(UcLetter);

  Prop* dummy = prop_new();
  *head = prop_add(*head, dummy);
  
  prop_ident(head);
  prop_value(head);
}

static void node(Node** head) {
  match(';');

  Node* dummy = node_new();
  *head = node_add(*head, dummy);

  for(;;) {
    if(!isupper((int)ch))
      break;
    property(&(*head)->prop);
  }
}

static void sequence(Node** head) {
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

static void game_tree(Node** head) {
  match('(');
  match_only(';');

  Node* dummy;
  
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

Node* parse(const char* filename) {
  Node* root = NULL;
  
  fp = fopen(filename, "r");

  if(!fp)
    return NULL;

  step_n();
  game_tree(&root);
  
  fclose(fp);
  return root;
}

#endif /* _PARSE_H */
