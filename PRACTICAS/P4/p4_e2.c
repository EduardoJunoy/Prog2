#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search_queue.h"
#include "file_utils.h"

#define MAX_C 1024

int main(int argc, char *argv[]) {
    if (argc != 3) { 
        fprintf(stderr, "Número de argumentos inválido\n");
        return 1;
    }

    FILE *f1=NULL, *f2=NULL;
    f1 = fopen(argv[1], "r");
    if (!f1) return 1;

    f2 = fopen(argv[2], "w");
    if (!f2) {
        fclose(f1);
        return 1;
    }

    SearchQueue *sq=NULL;
    sq = search_queue_new(char_print, char_cmp);
    if (!sq) {
        fclose(f1);
        fclose(f2);
        return 1;
    }

    char buffer[MAX_C];
    while (fgets(buffer, MAX_C, f1) != NULL) {
        size_t len = strlen(buffer);
        char *str = (char *) malloc(len + 1);

        if (str == NULL) {
            fclose(f1);
            fclose(f2);
            search_queue_free(sq);
            return EXIT_FAILURE;
        }
        strcpy(str, buffer);
        printf("%s", str);

        search_queue_push(sq, str);
    }

    search_queue_print(stdout, sq);
    /*while(!search_queue_isEmpty(sq)) {
        char *e = (char *)search_queue_pop(sq);
        fprintf(f2, "%s", e);
        free(e);
    }*/

    fclose(f1);
    fclose(f2);
    search_queue_free(sq);

    return 0;
}