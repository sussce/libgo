#ifndef _HASH_H_
#define _HASH_H_

#define MUL 29
#define SIZE 1024

typedef struct _p_entry p_entry;

struct _p_entry {
  char* id;
  uint token;
  ulong uid;
  
  int (*check)();  
  void (*exec)();
  int data;
};
struct _dict {
  int size;  
  int n;
  p_entry** hash;
};

static ulong hash(const char* key) {
  const uchar* p;
  ulong h;

  h = 0;
  for(p = (const uchar*)key; *p; p++)
    h = h * MUL + *p;

  return h;
}

elt* hash_get(Dict dict, char* key) {
  p_entry* e;
  int uid;

  uid = hash(key);
  e = *(dict->hash + uid % dict->size);
  return e;
}

#endif /* _HASH_H_ */
