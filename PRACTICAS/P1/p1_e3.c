#include <stdio.h>
#include "graph.h"

int main( int argc, char *argv[ ] ) {
    FILE *f=NULL;
    Graph *g=NULL;

    if (argc<2) {
        fprintf(stdout, "Faltan argumentos\n");
        return 1;
    }

    f = fopen(argv[1], "r");
    if (!f) return 1;

    g = graph_init();
    if (!g) return 1;

    if (graph_readFromFile(f, g) == ERROR)
        return 1;
    
    graph_print(stdout, g);

    graph_free(g);
    fclose(f);
    return 0;
}