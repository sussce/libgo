#ifndef __GM1_HASH_H__
#define __GM1_HASH_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#define MUL 29
#define SIZE 1024

typedef struct _hprop_entry hprop_entry;
typedef struct _hprop_dict hprop_dict;

struct hprop_entry {
  char* id;
  uint token;
  ulong uid;
  
  int (*check)();

  hprop_entry* next;
};
struct _hprop_dict {
  int size;
  int n_entry;
  hprop_entry** htable;
};

static ulong hash_prop(const char* key) {
  const uchar* p;
  ulong h;

  h = 0;
  for(p = (const uchar*)key; *p; p++)
    h = h * MUL + *p;

  return h;
}

static hprop_entry* hprop_search(hprop_dict* dict, const char* key) {
  hprop_entry* p;
  int h;

  h = hash_prop(key);
  for(p = *(dict->htable + h % dict->size);
      p != NULL;
      p = p->next) {
    if(!strcmp(p->id, key))
      return p;
  }
  return NULL
}

#endif /* __GM1_HASH_H__ */
