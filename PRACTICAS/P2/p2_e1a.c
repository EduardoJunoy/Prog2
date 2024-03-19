#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "file_utils.h"

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout);

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout) {
    float *elem;
    Stack *saux;

    if (!sin1 || !sin2 || !sout)
        return ERROR;

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE) {
        if (float_cmp(stack_top(sin1),stack_top(sin2))>0)
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
    float *e1 = NULL, *e2 = NULL;
    FILE *f2;
    FILE *f1;

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

    fscanf(f1, "%d", &size1);

    f2 = fopen(argv[2], "r");
    if (!f2)
    {
        fclose(f1);
        stack_free(sin1);
        stack_free(sin2);
        stack_free(sout);
        return -1;
    }

    fscanf(f2, "%d", &size2);

    e1 = (float *)malloc((size1) * sizeof(float));
    if (!e1)
    {
        fclose(f1);
        fclose(f2);
        stack_free(sin1);
        stack_free(sin2);
        stack_free(sout);
        return -1;
    }

    e2 = (float *)malloc((size2) * sizeof(float));
    if (!e2)
    {
        fclose(f1);
        fclose(f2);
        free(e1);
        stack_free(sin1);
        stack_free(sin2);
        stack_free(sout);
        return -1;
    }

    for (i=0; i<size1; i++)
    {
        fscanf(f1, "%f", &e1[i]);
        stack_push(sin1, &e1[i]);
    }

    for (i=0; i<size2; i++)
    {
        fscanf(f2, "%f", &e2[i]);
        stack_push(sin2, &e2[i]);
    }

    printf("Ranking 0:\n");
    stack_print(stdout, sin1, float_print);

    printf("Ranking 1:\n");
    stack_print(stdout, sin2, float_print);

    mergeStacks(sin1, sin2, sout);
    printf("Joint Ranking:\n");
    stack_print(stdout, sout, float_print);

    free(e1);
    free(e2);

    fclose(f1);
    fclose(f2);

    
    stack_free(sin1);
    stack_free(sin2);
    stack_free(sout);

    return 0;
}
