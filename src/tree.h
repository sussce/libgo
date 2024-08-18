#ifndef _TREE_H_
#define _TREE_H_

static int id = 0;

typedef struct _T T;
typedef struct _L L;

struct _T {
  T* prev;
  T* next;
  T* sib;
  int id;  
};
struct _L {
  L* prev;
  L* next;
};

static inline void t_init(T* t) {
  t->prev = NULL;
  t->next = NULL;
  t->sib = NULL;
  t->id = id++;
}

static inline T* t_add(T* head, T* t) {
  if(!head)
    return t;

  t->prev = head;

  if(!head->next) {
     head->next = t;
     return t;
  }

  for(head = head->next;
      head->sib != NULL;
      head = head->sib);

  head->sib = t;

  return t;
}
  
static inline void l_init(L* l) {
  l->prev = l;
  l->next = l;
}

static inline L* l_add(L* head, L* l) {
  if(!head)
    return l;

  l->prev = head->prev;
  l->next = head;
  head->prev->next = l;
  head->prev = l;
  
  return l;
}
#endif /* _TREE_H_ */
