#ifndef _TREE_H_
#define _TREE_H_

#include <string.h>

typedef struct _T T;
typedef struct _L L;
struct _T {
  T *prev, *next;
  T *prev_sib, *next_sib;

  int id;
};
struct _L {
  L* next;
};
enum {
  in_unset = 0, /* 0u */
  in_root = 1<<0, /* 1u */
  in_node = 1<<1, /* 2u */
  in_next = 1<<2, /* 4u */
  in_sib = 1<<3, /* 8u */
  in_pid = 1<<4, /* 16u */
  in_pv = 1<<5 /* 32U */
};

typedef void (*callback) (...);

static int id_atomic = 0;

void t_print (T* t);
T* t_fork (char** curr, T* pt, int prev);
void t_pre_order (T* t, callback call);

T* t_last_sib (T* t);
T* t_del (int id);
T* t_add (T* t, int id);
T* t_new ();

T* t_fork (char** curr, T* pt, int prev) {
  T *root = NULL, *t = pt;
  int inchar = in_unset;

  while ((*curr) < (*curr) + strlen ((*curr))) {
    if (**curr == '(') {
      //check_flag (*curr, in);
      if ((inchar != in_unset) && !(inchar & in_node) &&
          (inchar != in_next) && (inchar != in_sib)) {
        fprintf (stderr, "error, char %c must follow chars rn)\n", **curr);
        exit (-1);
      }

      if ((inchar != in_unset) && (inchar != in_root))
        t_fork (curr, t, in_node);

      if (inchar == in_unset)
        inchar = in_root;
      else if (inchar == in_next)
        inchar = in_sib;
      else if (inchar == in_node)
        inchar = in_next;
      else if (inchar == in_root)
        inchar = in_node;
    }
    else if (**curr == ')') {
      /* ?if extra sib ) */
      if (!(inchar & in_node) && (inchar != in_sib)) {
        fprintf (stderr, "error, char %c must follow chars n)\n", **curr);
        exit (-1);
      }
      
      return root;
    }
    else if (!isspace ((unsigned char)(**curr))) {
      if ((inchar != in_root) && !(inchar & in_node)) {
        fprintf (stderr, "error, char %c must follow chars n(\n", **curr);
        exit (-1);
      }
      
      t = t_add (t, **curr - '0');
      
      if (inchar == in_root)
        root = t;
 
      if (inchar == in_root)
        inchar = in_node | prev;
      else if (inchar & in_root)
        inchar &= ~in_root;
    }

    (*curr)++;
  }

  fprintf(stderr, "error, char ) must follow\n");
  exit (-1);
}

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

void t_seq (T* t, callback call) {
  if (t == NULL)
    return;

  t_seq (t->next, call);  
  t_seq (t->next_sib, call);
  call (t);
  
}

T* t_last_sib (T* t) {
  T* _t;
  for (_t = t->next;
       _t!= NULL && _t->next_sib != NULL;
       _t = _t->next_sib);
  
  if (_t == NULL)
    return t;

  return _t;
}

T* t_add (T* t, int id) {
  T* new = t_new ();
  T* _t;

  new->id = id; //_id++;
  
  if (t == NULL) {
    return new;
  }
  
  _t = t_last_sib (t);
  
  if (_t->next == NULL) {
    _t->next = new;
    new->prev = _t;
  }
  else { 
    _t->next_sib = new;
    new->prev = t;
    new->prev_sib = _t;
  }

  return new;
}

T* t_new () {
  T* new = malloc (sizeof (T));
  return new;
}

#endif /* _TREE_H_ */
