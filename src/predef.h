#ifndef _PRE_DEF_H_
#define _PRE_DEF_H_

#include <stddef.h>
#include <assert.h>

typedef unsigned int uint;
typedef unsigned long ulong;

#define typeof_member(T, m)	typeof(((T*)0)->m)

#define __same_type(a, b) \
  __builtin_types_compatible_p(typeof(a), typeof(b))

#define container_of(ptr, type, member) ({ \
	void *__mptr = (void *)(ptr); \
	static_assert(__same_type(*(ptr), ((type *)0)->member) ||	\
		      __same_type(*(ptr), void), \
		      "pointer type mismatch in container_of()");	\
	((type *)(__mptr - offsetof(type, member))); })

#endif /* _PRE_DEF_H_ */
