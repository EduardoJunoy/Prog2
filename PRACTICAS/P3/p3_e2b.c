#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"

int main(int argc, char *argv[])
{
    Graph *g = NULL;
    FILE *f = NULL;
    long n1, n2;

    if (argc != 4)
    {
        fprintf(stderr, "Numero de argumentos incorrecto\n");
        return -1;
    }

    n1 = (long)atoi(argv[2]);
    n2 = (long)atoi(argv[3]);
    
    f = fopen(argv[1], "r");
    g = graph_init();
    if (!g){
        fclose(f);
        return EXIT_FAILURE;
    }

    if (graph_readFromFile(f, g) == ERROR)
    {
        graph_free(g);
        fclose(f);
        return -1;
    }

    fprintf(stdout, "Input graph:\n");
    graph_print(stdout, g);

    fprintf(stdout, "--------DFS------------\n");
    fprintf(stdout, "From Vertex id: %ld\n", n1);
    fprintf(stdout, "To Vertex id: %ld\n", n2);
    fprintf(stdout, "Output:\n");

    if (graph_depthSearch(g, n1, n2) == ERROR)
    {
        graph_free(g);
        return -1;
    }

    fprintf(stdout, "--------BFS------------\n");
    fprintf(stdout, "From Vertex id: %ld\n", n1);
    fprintf(stdout, "To Vertex id: %ld\n", n2);
    fprintf(stdout, "Output:\n");

    if (graph_breathSearch(g, n1, n2) == ERROR)
    {
        graph_free(g);
        return -1;
    }

    fclose(f);
    graph_free(g);

    return 0;
}