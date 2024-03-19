#include <stdio.h>
#include "graph.h"

int main () {
    Graph *g=NULL;
    long *arr=NULL;
    int i;
    
    g = graph_init();
    if (!g) {
        printf("Fallo al tratar de crear el grafo");
        return 1;
    }
    
    printf("Inserting Madrid... result...: ");
    if (graph_newVertex(g, "id:111 tag:Madrid state:0") == OK)
        printf("1\n");
    
    else { 
        printf("-1\n");
        return 1;
    }
    

    
    printf("Inserting Toledo... result...: ");
    if (graph_newVertex(g, "id:222 tag:Toledo state:0") == OK)
        printf("1\n");
    
    else {
        printf("-1\n");
        return 1;
    }
    
    
    printf("Inserting edge: 222 --> 111\n");
    graph_newEdge(g, 222, 111);

    
    printf("111 --> 222? ");
    if (graph_connectionExists(g, 111, 222) == TRUE)
        printf("Yes\n");
    else 
        printf("No\n");

    
    printf("222 --> 111? ");
    if (graph_connectionExists(g, 222, 111) == TRUE)
        printf("Yes\n");
    else
        printf("No\n");
    
    
    printf("Number of connections from 111: %d\n", graph_getNumberOfConnectionsFromId(g, 111));
    printf("Number of connections from Toledo: %d\n", graph_getNumberOfConnectionsFromTag(g, "Toledo"));
    
    arr = graph_getConnectionsFromId(g, 222);

    
    for (i=0; i<graph_getNumberOfConnectionsFromTag(g, "Toledo"); i++)
        printf("Connections from Toledo: %ld\n", arr[i]); 
    
    graph_print(stdout, g);
    


    free(arr);
    graph_free(g);

    
    return 0;
}