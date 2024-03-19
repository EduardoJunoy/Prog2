#include "vertex.h"
#include <string.h>

#define TAG_LENGTH 64

/* START [_Vertex] */
struct _Vertex {
  long id;
  char tag[TAG_LENGTH];
  Label state;
  int index;
};
/* END [_Vertex] */

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/

Vertex *vertex_init(){
  Vertex *v = NULL;
  static int ind=0;
  
  v = (Vertex*)malloc(sizeof (Vertex));
  if (!v)
  {
    return NULL;
  }

  v->id = 0;
  v->tag[0] = '\0';
  v->state = WHITE;
  v->index = ind;
  ind++;

  return v;
}

void vertex_free(void *v){
  free(v);
}

long vertex_getId(const Vertex *v){
  if (!v)
    return -1;
  
  return v->id;
}

const char *vertex_getTag(const Vertex *v){
  if (!v)
    return NULL;
  
  return v->tag;
}

Label vertex_getState(const Vertex *v){
  if (!v)
    return ERROR_VERTEX;
  
  return v->state;
}

int vertex_getIndex(const Vertex *v){
  if (!v)
    return -1;
  
  return v->index;
}

Status vertex_setId(Vertex *v, const long id){
  if (!v || !id)
    return ERROR;
  
  v->id = id;
  
  return OK;
}

Status vertex_setTag(Vertex *v, const char *tag){
  if (!v || !tag)
    return ERROR;
  
  strcpy(v->tag, tag);

  return OK;
}

Status vertex_setState(Vertex *v, const Label state){
  if (!v || !state)
    return ERROR;
  
  v->state = state;

  return OK;
}

Status vertex_setIndex(Vertex *v, const int index){
  if (!v || !index)
    return ERROR;
  
  v->index = index;
  
  return OK;
}

int vertex_cmp(const void *v1, const void *v2){
  if (!v1 || !v2)
    return 0;

  int diff = 0;
  int id1 = vertex_getId(v1);
  int id2 = vertex_getId(v2);

  char tag1[TAG_LENGTH]; 
  char tag2[TAG_LENGTH];

  strcpy(tag1, vertex_getTag(v1));
  strcpy(tag2, vertex_getTag(v2));


  if (id1 == id2) {
    if (strcmp(tag1, tag2) == 0)
      return 0;
    
    else {
      diff = strcmp(tag1, tag2);
      return diff;
    }
  }

  else{
    diff = (id1)-(id2);
    return diff;
  }
}



void *vertex_copy(const void *src){
  Vertex *trg=NULL;

  if (!src) return NULL;

  trg = (Vertex *) malloc(sizeof(Vertex));
  if (!trg) return NULL;

  trg->id = vertex_getId(src);
  trg->state = vertex_getState(src);
  strcpy(trg->tag, vertex_getTag(src));
  trg->index = vertex_getIndex(src);

  return trg;
}

int vertex_print(FILE *pf, const void *v){
  int id;
  char tag[TAG_LENGTH];
  int state;
  int index;

  if(!pf || !v) return -1;

  id = vertex_getId(v);
  strcpy(tag, vertex_getTag(v));
  state = vertex_getState(v);
  index = vertex_getIndex(v);
  
  return fprintf(pf, "[%d, %s, %d, %d] ", id, tag, state, index);
}