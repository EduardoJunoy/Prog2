#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacityç

struct _Stack {
    void **item; /*!<Static array of elements*/
    int top; /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};


Stack * stack_init (){
    Stack *s = NULL;

    s = (Stack *) malloc(sizeof(Stack));
    if (s == NULL) {
    return NULL;
    }
    s->item = malloc(INIT_CAPACITY * sizeof(void *));
    s->top = -1;
    s->capacity = INIT_CAPACITY;

    return s;
}

void stack_free (Stack *s){
    free(s->item);
    free(s);
}

void stack_resize(Stack *s) {
    void **new_item;
    
    s->capacity += FCT_CAPACITY;
    new_item = realloc(s->item, s->capacity * sizeof(void *));
    s->item = new_item;
}

Status stack_push (Stack *s, const void *ele){
    if (s == NULL || ele == NULL){
        return ERROR;
    }
    if(s->top == s->capacity - 1){
        stack_resize(s);
    }

    s->top++;
    s->item[s->top] = (void *)ele;
    return OK;
}

void * stack_pop (Stack *s){
    void *e = NULL;
    if (s == NULL || s->top == -1) {
        return NULL;
    }
    e = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;
    return e;
}

void * stack_top (const Stack *s){
    if (s == NULL || s->top == -1) {
        return NULL;
    }
    return s->item[s->top];
}

size_t stack_size (const Stack *s){
    if (!s){
        return -1;
    }
    return s->top+1;
}

int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f){
    int i, printed;

    if (!s || fp == NULL) return -1;

    printed=fprintf(fp, "SIZE: %d\n", s->top+1);
    for(i=s->top; i>=0; i--){
        printed += f(fp, s->item[i]);
        printf("\n");
    }
    return printed;
}

Bool stack_isFull (Stack *s) {
    if (s == NULL) {
        return TRUE;
    }
    if (s ->top == s->capacity- 1) {
        return TRUE;
    }
    return FALSE;
}

Bool stack_isEmpty (const Stack *s){
    if (s == NULL) {
        return TRUE;
    }
    if (s ->top == -1) {
        return TRUE;
    }
    return FALSE;
}
