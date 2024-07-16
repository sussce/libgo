#ifndef _HASH_H_
#define _HASH_H_

#define MUL 29
#define SIZE 1024

struct _elt {
  char* id;

  unsigned int token;
  unsigned long uid;
  
  int (*check) (Prop* prop);
  void (*exec) (Prop* prop);
  int data;
};
struct _dict {
  int size;  
  int n;
  elt** hash;
};

static unsigned long hash_prop(const char* key) {
  unsigned const char* p;
  unsigned long h;

  h = 0;
  for(p = (unsigned const char*)key; *p; p++)
    h = h * MUL + *p;

  return h;
}

hash_add();

elt* hash_get(Dict dict, char* key) {
  elt* e;
  int uid;

  uid = hash(key);
  e = *(dict->hash + uid % dict->size);
  return e;
}

#endif /* _HASH_H_ */
