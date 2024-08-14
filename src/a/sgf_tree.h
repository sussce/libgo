#ifndef _SGF_TREE_H_
#define _SGF_TREE_H_

#include <stdlib.h>
#include <ctype.h>

#include "tree.h"
#include "node.h"
#include "prop.h"

static FILE* fp;
static int ch;

#define UcLetter 0xfe
#define is_char(c) ((ch) == (c))
#define step() ((ch) = getc(fp))

void g_error(const char* msg, int arg) {
  fprintf(stderr, msg, arg);
  exit(-1);
}

void g_assert(int cond, const char* msg, int arg) {
  if(!cond)
    g_error(msg, arg);
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
    g_assert(isupper((int)ch), "miss UcLetter\n", 0);
  else
    g_assert(is_char(c), "miss %c\n", c);
}

static inline void match(char c) {
  match_only(c);
  step_n();
}

static void property_id(Prop** head) {
  match_only(UcLetter);

  char* id = malloc(125*sizeof(char));
  char* p = id;
  
  for(;;) {
    if(!is_char('[') && !isupper((int)ch))
      g_error("miss UcLetter\n", 0);
    if(is_char('['))
      break;

    *p++ = ch;
    step();
  }
  *p = '\0';

  (*head)->id = id;
  printf("%s\n", (*head)->id);
  
  match_only('[');
}

static void property_value(Prop** head) {
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

  Prop* new = prop_new();
  *head = prop_add(*head, new);
  
  property_id(head);
  property_value(head);
}

static void node(Node** head) {
  match(';');

  Node* new = node_new();
  *head = node_add(*head, new);

  for(;;) {
    if(!isupper((int)ch))
      break;
    property(&(*head)->prop);
  }
}

static Node* sequence(Node** head) {
  match_only(';');

  Node** root = NULL;
  Node* tmp;
  
  if(!*head)
    root = head;  
  tmp = *head;
  head = &tmp;
  
  for(;;) {
    if(!is_char(';'))
      break;
    node(head);

    if(root && !*root)
      *root = *head;
  }

  return tmp;
}

static void gtree(Node** head) {
  match('(');
  match_only(';');

  Node* last = sequence(head);

  for(;;) {
    if(!is_char('('))
      break;
    gtree(&last);
  }

  match(')');
}

static void collection() {}

Node* gparse(const char* filename) {
  Node* root = NULL;
  
  fp = fopen(filename, "r");

  if(!fp)
    return NULL;

  step_n();
  gtree(&root);

  fclose(fp);
  return root;
}

#endif /* _SGF_TREE_H */
