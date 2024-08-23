#include "prop.h"
#include "error.h"

#include <stdlib.h>

gprop* prop_new() {
  gprop* new = malloc(sizeof(gprop));

  if(!new)
    gerror("prop_new(), out of memory\n", 0);

  new->id = NULL;
  new->value = NULL;
  new->tkn = 0;
  new->uid = 0;
  l_init(&new->l);

  return new;
}

gprop* prop_add(gprop* head, gprop* prop) {
  if(!head)
    return prop;

  l_add(&head->l, &prop->l);
  return prop;
}
