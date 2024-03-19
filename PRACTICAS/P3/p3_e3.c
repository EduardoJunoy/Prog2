#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "file_utils.h"

int main(int argc, char *argv[]) {
    List *l=NULL, *l2=NULL;
    FILE *f = NULL;
    int size=0, i, orden=0;
    float *arr=NULL, *float_element=NULL;

    if (argc != 3) return -1;

    f = fopen(argv[1], "r");
    if (f == NULL) return -1;

    orden = atoi(argv[2]);

    l = list_new();
    if (l == NULL) {
        fclose(f);
        return -1;
    }  

    fscanf(f, "%d", &size);

    arr = (float *) malloc(size * sizeof(float));
    if (arr == NULL) {
        fclose(f);
        list_free(l);
    }

    fgetc(f);

    for (i=0; i<size; i++) {
        fscanf(f, "%f", &arr[i]);
        list_pushBack(l, &arr[i]);
        
        i++;

        fscanf(f, "%f", &arr[i]);
        list_pushFront(l, &arr[i]);
    }

    list_print(stdout, l, float_print);

    l2 = list_new();
    if (l2 == NULL) {
        fclose(f);
        list_free(l);
        free(arr);
        return -1;
    }

    fprintf(stdout, "\nFinished inserting. Now we extract from the beginning and insert in order:\n");

    for (i=0; i<(size/2); i++) {
        float_element = list_popFront(l);
        fprintf(stdout, "%f ", *float_element);
        list_pushInOrder(l2, float_element, float_cmp, orden);
    }


    fprintf(stdout, "\nNow we extract from the end and insert in order:\n");

    for (i=0; i<(size/2); i++) {
        float_element = list_popBack(l);
        fprintf(stdout, "%f ", *float_element);
        list_pushInOrder(l2, float_element, float_cmp, orden);
    }

    fprintf(stdout, "\n");

    list_print(stdout, l2, float_print);
    fprintf(stdout, "\n");


    
    list_free(l);
    list_free(l2);
    free(arr);
    fclose(f);  

    return 0;
}