#include <stdio.h>
#include <ctype.h>
#include "node.h"

/*
( ;
; C
C [   
[ v
[.. ]
] C;()
) ()

(;FF[4] SZ[19]
 ;B[aa] C[a1] ;W[b]]C[b1]] (;B[cc]C[c1] ;W[dd]C[d1]) (;B[ee]C[e1] ;W[ff]C[f1]))
*/

int check_pid (char** pid) {
  char *end = *pid + strlen (*pid),
    *new = NULL;
  
  if (!pid || !*pid)
    return 0;

  // remove tail space
  // invalid
  for (char *p = *pid; p < end; p++)
    if (!isupper ((int)(*p)))
      return 0;

  // unknown
  
  return 1;
}

//char p[] = {'\', '[', '4', '\', ']', '\0'};
int check_pv (char** pv) {
  char *end = *pv + strlen (*pv),
    *new = NULL;
  int sz = 0;
  
  if (!pv || !*pv)
    return 0; 

  // remove '\'
  for (char* p = *pv; p < end; p++)
    if (*p != '\\')
      sz++;

  if (sz != strlen (*pv)) {
    new = malloc (sz*sizeof (char));
    
    for (char *p = *pv, *des = new; p < end; p++)
      if (*p != '\\')
        *des++ = *p;
  } else {
    new = *pv;
  }
  
  // check
  if (!1) {
    if (sz != strlen (*pv))
      free (new);
    return 0;
  }
  
  if (sz != strlen (*pv)) {
    free (*pv);
    *pv = new;
  }
  
  return 1;
}

Prop* n_prop_add(char** curr, Prop* pprop) {
  Prop* prop = NULL;
  char* pos = NULL;
  int inchar = in_unset;

  while (*curr < (*curr + strlen(*curr))) {
    if (isalpha ((int)(**curr))) {
      if (inchar != in_unset && inchar != in_pid && !(inchar & in_pv)) {
        fprintf (stderr, "char %c must follow chars ;[]c", **curr);
        exit (-1);
      }
      
      if (inchar & in_pv) {
        (*curr)++;
        continue;
      }
      
      if (inchar == in_unset) {
        prop = n_prop_new ();
        pos = *curr;
      }
      
      if (inchar == in_unset)
        inchar = in_pid;
    }
    else if (**curr == '[') {
      char* pid = NULL;

      if (inchar != in_pid && !(inchar & in_pv)) {
        fprintf (stderr, "error, char %c must follow chars c\\", **curr);
        exit (-1);
      }
      
      if (inchar & in_pv) {
        (*curr)++;
        continue;
      }
      
      // get pid
      pid = malloc ((*curr - pos + 1)*sizeof (char));
      memcpy (pid, pos, *curr - pos);
       
      // check pid
      if (!check_pid (&pid)) {}
      prop->id = pid;
      
      pos = *curr + 1;
      inchar |= in_pv;
    }
    else if (**curr == ']') {
      char* pv = NULL;

      if (!(inchar & in_pv)) {
        fprintf (stderr, "error, char %c must follow chars [..\n", **curr);
        exit (-1);
      }
      
      if (*(*curr - 1) == '\\') {
        (*curr)++;
        continue;
      }
      
      // get pv
      pv = malloc ((*curr - pos + 1)*sizeof (char));
      memcpy (pv, pos, *curr - pos);
      
      // check pv
      if (!check_pv (&pv)) {}
      prop->value = pv;
      
      return prop;
    }
    
    (*curr)++;
  }

  if (inchar == in_pid) {
    fprintf (stderr, "error, char [ must follow\n");
  }
  else {
    fprintf (stderr, "error, char ] must follow\n");
  }
  exit (-1);
}

Node* n_add(char** curr, Node* pnode, int prev) {
  Node* node = NULL;
  Prop* prop = NULL;
  int inchar = in_unset;

  if (prev == in_root){
    printf ("root, ");
  }
  else {
    printf ("node, ");
  }
  
  while (*curr < (*curr + strlen(*curr))) {
    if (**curr == '(') {
      if (inchar != in_pv) {
        fprintf (stderr, "error, char %c must follow char ]\n", **curr);
        exit (-1);
      }
      
      return node;
    }
    else if (**curr == ')') {
      if (inchar != in_pv) {
        fprintf (stderr, "error, char %c must follow char ]\n", **curr);
        exit (-1);
      }

      return node;
    }
    else if (**curr == ';') {
      if (inchar != in_unset && inchar != in_pv) {
        fprintf (stderr, "error, char %c must follow char ]\n", **curr);
        exit (-1);
      }
      
      if (inchar != in_unset)
        return node;

      node = n_new ();
      inchar = in_node;
    }
    else if (isalpha ((int)(**curr))) {
      if (inchar != in_node && inchar != in_pv) {
        fprintf (stderr, "error, char %c must follow chars ;]\n", **curr);
        exit (-1);
      }

      prop = n_prop_add (curr, prop);
      printf ("%s[%s]", prop->id, prop->value);
      
      inchar = in_pv;
    }
    else {
      if (!isspace ((int)(**curr))) {
        fprintf (stderr, "error, char %c unknown\n", **curr);
        exit (-1);
      }
    }
    
    (*curr)++;
  }

  if (inchar == in_node) {
    fprintf (stderr, "error, chars must follow char ;\n");
  }
  else {
    fprintf (stderr, "error, char ) must follow\n");
  }
  exit (-1);
}

Node* n_fork(char** curr, Node* pnode, int prev) {
  Node *root = NULL,
    *node = pnode;
  int inchar = in_unset;

  while (*curr < (*curr + strlen (*curr))) {
    if (**curr == '(') {
      if ((inchar != in_unset) && !(inchar & in_node) &&
          (inchar != in_next) && (inchar != in_sib)) {
        fprintf (stderr, "error, char %c must follow chars rn)\n", **curr);
        exit (-1);
      }
      
      if ((inchar != in_unset) && (inchar != in_root))
        n_fork (curr, node, in_node);

      if (inchar == in_unset)
        inchar = in_root;
      else if (inchar == in_root)
        inchar = in_node;
      else if (inchar == in_node)
        inchar = in_next;
      else if (inchar == in_next)
        inchar = in_sib;
    }
    else if (**curr == ')') {
      if (inchar == in_root) {
        fprintf (stderr, "error, no chars before char )\n");
        exit (-1);
      }

      if (!(inchar & in_node) && (inchar != in_sib)) {
        fprintf (stderr, "error, char %c must follow chars n)\n", **curr);
        exit (-1);
      }

      return root;
    }
    else if (**curr == ';') {
      if (inchar != in_root && !(inchar & in_node) &&
          inchar != in_next && inchar != in_sib) {
        fprintf (stderr, "error, char %c must follow chars n(\n", **curr);
        exit (-1);
      }

      node = n_add (curr, node,
                    ((inchar == in_root) && (prev == in_root)) ?
                    in_root : in_node);
      printf ("\n");
      
      if (inchar == in_root)
        root = node;
      
      if (inchar == in_root)
        inchar = in_node | prev;
      else if (inchar & in_root)
        inchar &= ~in_root;
      
      continue;
    }
    else {
      if (!isspace ((int)(**curr))) {
        fprintf (stderr, "error, char %c unknown\n", **curr);
        exit (-1);
      }
    }

    (*curr)++;
  }

  if (inchar == in_unset) {
    fprintf (stderr, "error, char ( must follow\n");
  }
  else {
    fprintf (stderr, "error, char ) must follow\n");
  }
  exit (-1);
}

int main (int argc, char** argv) {
 /*  char* order =" (;F F [\\[4\\]] S Z [\\(19\\) \\;sz] \ */
/* ;B[aa]C[a1] ;W[bb]C[b1] (;B[cc]C[c1] ;W[dd]C[d1]) (;B[ee]C[e1] ;W[ff]C[f1]))"; */
  char* order = "(;F F [ 4[ (sz ]  )";
  char* curr = order;
  
  //Node* n = n_fork (&curr, NULL, in_root);
  return 0;
}
