#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned int uint;
typedef unsigned long ulong;

/* enum { */
/*   in_unset = 0, /\* 0u *\/ */
/*   in_root = 1<<0, /\* 1u *\/ */
/*   in_node = 1<<1, /\* 2u *\/ */
/*   in_next = 1<<2, /\* 4u *\/ */
/*   in_sib = 1<<3, /\* 8u *\/ */
/*   in_pid = 1<<4, /\* 16u *\/ */
/*   in_pv = 1<<5 /\* 32U *\/ */
/* }; */

#define in_unset 0u
#define in_root 1u
#define in_node 2u
#define in_next 4u
#define in_sib 8u
#define in_pid 16u
#define in_pv 32u

typedef struct _T T;
typedef struct _L L;

struct _T {
  uint id;
  
  T *prev, *next;
  T *prev_sib, *next_sib;
};
struct _L {
  L* next;
};

static uint id_atomic = 0;

typedef void (*t_call)(T* t);

L* l_add(L* l, L* pl);
L* l_new();

T* t_parse_order(char** curr, T* pt, uint prev);
void t_seq(T* t, t_call call);
T* t_add(T* t, T* pt);
T* t_new(int id);

/*
        4
      /   \
     2-----x
   / | \   |
  1--5--9  y
 /  /   |
3  7    8
  / 
 6    


 0—a—b—c
 │ └-d—e
 └-f—g—h—i
   └-j

 R—B—W—B
 │ └-W—B   
 └-B—W—B—W
   └-W
 
pre_nlr 4 2 1 3 5 7 6 9 8 72 73
pre_nrl y x 8 9 6 7 5 3 1 2 4
post_lrn 3 1 6 7 5 8 9 2 73 72 4
post_lr+n 3 6 7 8 9 5 1 y x 2 4 

level 4 2 x 1 5 9 y 3 7 8 6
*/

L* l_add(L* l, L* pl) {
  if(pl == NULL)
    return l;

  for(; pl->next != NULL;
      pl = pl->next);

  pl->next = l;
  
  return l;
}

L* l_new() {
  L* new = (L*)malloc(sizeof(L));

  if(new == NULL) {
    fprintf(stderr, "l_new(): mem alloc failed\n");
    exit(-1);
  }

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
  if(t == NULL)
    return;

  call(t);
  t_seq(t->next, call);  
  t_seq(t->next_sib, call);
}

T* t_add(T* t, T* pt) {
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

T* t_new(int id) {
  T* new = (T*)malloc(sizeof(T));

  if(new == NULL) {
    fprintf(stderr, "t_new(), mem alloc failed\n");
    exit(-1);
  }
  
  memset(new, 0, sizeof(T));
  new->id = id == -1 ? id_atomic : id;
  id_atomic++;
  
  return new;
}

#endif /* _TREE_H_ */
