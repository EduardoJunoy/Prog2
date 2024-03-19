#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "file_utils.h"
#include "vertex.h"

typedef int (*element_cmp)(const void *e1, const void *e2);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, element_cmp cmp);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, element_cmp cmp) {
    void *elem;
    Stack *saux;

    if (!sin1 || !sin2 || !sout)
        return ERROR;

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE) {
        if (cmp(stack_top(sin1),stack_top(sin2))>0)
            elem = stack_pop(sin1);
        
        else
            elem = stack_pop(sin2);
        
        stack_push(sout, elem);
    }

    if (stack_isEmpty(sin1) == TRUE)
        saux = sin2;
    
    else
        saux = sin1;
    
    while (stack_isEmpty(saux) == FALSE) {
        elem = stack_pop(saux);
        stack_push(sout, elem);
    }

    return OK;
}

int main(int argc, char *argv[]) {
    Stack *sin1 = NULL, *sin2 = NULL, *sout = NULL;
    int i, size1, size2;
    Vertex *e1[1024], *e2[1024];
    FILE *f2;
    FILE *f1;
    char desc[1024];

    if (argc != 3) {
        fprintf(stderr, "Faltan argumentos\n");
        return -1;
    }

    sin1 = stack_init();
    if (!sin1)
        return -1;

    sin2 = stack_init();
    if (!sin2) {
        stack_free(sin1);
        return -1;
    }

    sout = stack_init();
    if (!sout) {
        stack_free(sin1);
        stack_free(sin2);
        return -1;
    }

    f1 = fopen(argv[1], "r");
    if (!f1)
    {
        stack_free(sin1);
        stack_free(sin2);
        stack_free(sout);
        return -1;
    }

    f2 = fopen(argv[2], "r");
    if (!f2)
    {
        fclose(f1);
        stack_free(sin1);
        stack_free(sin2);
        stack_free(sout);
        return -1;
    }


    fscanf(f1, "%d", &size1);
    fgetc(f1);

    for (i=0; i<size1; i++) {
        fgets(desc, 1024, f1);
        e1[i] = vertex_initFromString(desc);
        stack_push(sin1, e1[i]);
    }

    fscanf(f2, "%d", &size2);
    fgetc(f2);


    for (i=0; i<size2; i++) {
        fgets(desc, 1024, f2);
        e2[i] = vertex_initFromString(desc);
        stack_push(sin2, e2[i]);
    }



    printf("Ranking 0:\n");
    stack_print(stdout, sin1, vertex_print);

    printf("Ranking 1:\n");
    stack_print(stdout, sin2, vertex_print);

    mergeStacks(sin1, sin2, sout, vertex_cmp);
    printf("Joint Ranking:\n");
    stack_print(stdout, sout, vertex_print);

    for(i=0; i<size1; i++) {
        vertex_free(e1[i]);
    }

    for(i=0; i<size2; i++) {
        vertex_free(e2[i]);
    }

    fclose(f1);
    fclose(f2);
    
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);

    return 0;
}
