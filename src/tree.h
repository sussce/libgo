#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "predef.h"

#define read_once(var, val) 
#define write_once(var, val) (var = val)
  
#define t_ptr(ptr, type, member) \
  container_of(ptr, type, member)

typedef struct _T T;
typedef struct _L L;

struct _T {
  uint id;
  
  T *prev, *next;
  T *prev_sib, *next_sib;
};
struct _L {
  L *prev, *next;
};

typedef void (*t_call)(T* t);

static uint id_atom = 0;

static void t_free(T* t) {}

static void l_free(L* l) {}

static inline void l_init(L* l) {
  write_once(l->prev, l);
  write_once(l->next, l);
}

static inline L* l_add(L* l, L* pl) {
  L* next;
  
  if(pl == NULL)
    return l;

  next = pl->next;
  
  l->prev = pl;
  l->next = next;
  pl->next = l;
  next->prev = l;
  
  return l;
}

static inline void t_init(T* t, int id) {
  write_once(t->id, id == -1 ? id_atom++ : id);
}

static inline T* t_add(T* t, T* pt) {
  if(pt == NULL)
    return t;

  if(pt->next == NULL) {
    pt->next = t;
    t->prev = pt;
  }
  else {
    T* sib;
    
    for(sib = pt->next;
        sib->next_sib != NULL;
        sib = sib->next_sib);
    
    sib->next_sib = t;
    t->prev_sib = sib;
    t->prev = pt;
  }

  return t;
}

static inline T* t_new(int id) {
  T* new = (T*)malloc(sizeof(T));

  if(new == NULL) {
    fprintf(stderr, "t_new(), mem alloc failed\n");
    exit(-1);
  }
  
  memset(new, 0, sizeof(T));
  t_init(new, id);
  
  return new;
}

T* t_parse_order(char** curr, T* pt, uint prev) {
  T *root = NULL,
    *t = pt;
  uint inchar = in_unset;

  while((*curr) < (*curr) + strlen ((*curr))) {
    if(**curr == '(') {
      //check_flag (*curr, in);
      if((inchar != in_unset) && !(inchar & in_node) &&
         (inchar != in_next) && (inchar != in_sib)) {
        fprintf(stderr, "error, char %c must follow chars rn)\n", **curr);
        exit(-1);
      }

      if((inchar != in_unset) && (inchar != in_root))
        t_parse_order(curr, t, in_node);

      if(inchar == in_unset)
        inchar = in_root;
      else if(inchar == in_next)
        inchar = in_sib;
      else if(inchar == in_node)
        inchar = in_next;
      else if(inchar == in_root)
        inchar = in_node;
    }
    else if(**curr == ')') {
      /* ?if extra sib ) */
      if(!(inchar & in_node) && (inchar != in_sib)) {
        fprintf(stderr, "error, char %c must follow chars n)\n", **curr);
        exit(-1);
      }
      
      return root;
    }
    else if(isdigit((int)(**curr))) {
      if((inchar != in_root) && !(inchar & in_node)) {
        fprintf(stderr, "error, char %c must follow chars n(\n", **curr);
        exit(-1);
      }

      t = t_add(t_new(**curr - '0'), t);     
      
      if(inchar == in_root)
        root = t;
 
      if(inchar == in_root)
        inchar = in_node | prev;
      else if(inchar & in_root)
        inchar &= ~in_root;
    }
    else {
      if(!isspace((int)(**curr))) {
        fprintf(stderr, "error, char %c unknown\n", **curr);
        exit(-1);
      }
    }

    (*curr)++;
  }

  fprintf(stderr, "error, char ) must follow\n");
  exit(-1);
}

void t_seq(T* t, t_call call) {
  call(t);

  if(t->next)
    t_seq(t->next, call);
  if(t->next_sib)
    t_seq(t->next_sib, call);
}

#endif /* _TREE_H_ */
