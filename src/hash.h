#ifndef __GM1_HASH_H__
#define __GM1_HASH_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#define MUL (29)
#define PROP_TABLE_SZ (1024)
#define LOAD_FACTOR (1)

typedef struct _hprop_entry hprop_entry;
typedef struct _hprop_dict hprop_dict;

struct _hprop_entry {
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

static hprop_dict* prop_dict;
static hpos_dict* pos_dict;

static void grow() {}

static ulong hash_prop(const char* key) {
  const uchar* p;
  ulong h;

  h = 0;
  for(p = (const uchar*)key; *p; p++)
    h = h * MUL + *p;

  return h;
}

void hprop_init() {
  __hprop_init(PROP_TABLE_SZ);
}

void __hprop_init(int size) {
  prop_dict = malloc(sizeof(hprop_dict));
  
  if(!new)
    gerror("hprop_init(), out of memory\n", 0);

  prop_dict->size = size;
  prop_dict->n_entry = 0;
  prop_dict->htable = malloc(sizeof(hprop_dict*) * prop_dict->size);

  for(int i = 0; i < prop_dict->size; i++)
    prop_dict->htable[i] = NULL;
}

hprop_entry* hprop_add(const char* key, uint tkn) {
  hprop_entry* new;
  ulong h;

  new = malloc(sizeof(hprop_entry));

  if(!new)
    gerror("hprop_add(), out of memory\n", 0);
  
  h = hash_prop(key) % prop_dict->size;

  new->next = prop_dict->htable[h];
  prop_dict->htable[h] = new;
  prop_dict->n_entry++;
  
  return new;
}

hprop_entry* hprop_get(hprop_dict* dict, const char* key) {
  hprop_entry* entry;
  int h;

  h = hash_prop(key) % prop_dict->size;
  
  for(entry = prop_dict->htable[h];
      entry != NULL;
      entry = entry->next)
    if(!strcmp(entry->id, key))
      return entry;
  
  return NULL;
}

#endif /* __GM1_HASH_H__ */
