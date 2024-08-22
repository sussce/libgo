#ifndef __GM1_TREE_H__
#define __GM1_TREE_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#include <stddef.h>
#include <assert.h>

#define typeof_member(T, m)	typeof(((T*)0)->m)

#define __same_type(a, b) \
  __builtin_types_compatible_p(typeof(a), typeof(b))

#define container_of(ptr, type, member) ({ \
	void *__mptr = (void *)(ptr); \
	static_assert(__same_type(*(ptr), ((type *)0)->member) ||	\
		      __same_type(*(ptr), void), \
		      "pointer type mismatch in container_of()");	\
	((type *)(__mptr - offsetof(type, member))); })

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

static int id = 0;

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

#endif /* __GM1_TREE_H__ */
