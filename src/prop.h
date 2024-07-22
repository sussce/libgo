#ifndef _PROP_H_
#define _PROP_H_

#include <string.h>
#include "tree.h"

typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct _Prop Prop;
typedef struct _Value Value;

struct _Value {
  char* v;
  L l;
};
struct _Prop {
  char* id;
  Value* value;
  uint token;
  ulong uid;
  L l; 
};

Value* v_add(Value* value, Value* pvalue);
Value* v_new();
Prop* p_add(Prop* prop, Prop* pprop);
Prop* p_new();

//p_find; 

Value* v_add(Value* value, Value* pvalue) {
  if(pvalue == NULL)
    return value;

  l_add(value->l, pvalue->l);
  
  return value;
}

Value* v_new() {
  Value* new = (Value*)malloc(sizeof(Value));

  if(new == NULL) {
    fprintf(stderr, "v_new(), mem alloc failed\n");
    exit(-1);
  }
  
  memset(new, 0, sizeof(Value));

  return new;
}

Prop* p_add(Prop* prop, Prop* pprop) {
  if(pprop == NULL)
    return prop;
 
  l_add(&(prop->l), &(pprop->l));

  return prop;
}

Prop* p_new() {
  Prop* new = (Prop*)malloc(sizeof(Prop));

  if(new == NULL) {
    fprintf(stderr, "p_new(), mem alloc failed\n");
    exit(-1);
  }
    
  memset(new, 0, sizeof(Prop));
   
  return new;
}

#endif /* _PROP_H_ */
