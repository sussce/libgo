#ifndef __GM1_HASH_H__
#define __GM1_HASH_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#define MUL 29
#define SIZE 1024

typedef struct _p_entry p_entry;

struct _p_entry {
  char* id;
  uint token;
  ulong uid;
  
  int (*check)();
};
struct _dict {
  int size;
  int n_entry;
  p_entry** hash;
};

static
ulong hash(const char* key) {
  const uchar* p;
  ulong h;

  h = 0;
  for(p = (const uchar*)key; *p; p++)
    h = h * MUL + *p;

  return h;
}

static
p_entry* hash_get(struct _dict* dict, const char* key) {
  p_entry* p;
  int uid;

  uid = hash(key);
  p = *(dict->hash + uid % dict->size);
  return p;
}

#endif /* __GM1_HASH_H__ */
