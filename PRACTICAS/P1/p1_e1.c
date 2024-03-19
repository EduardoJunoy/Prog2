#include <stdio.h>
#include "vertex.h"

int main()
{
    Vertex *v1 = NULL, *v2 = NULL, *v3=NULL;
    int cmp;

    /*Crear e inicializar dos vértices.*/
    v1 = vertex_init();
    if (!v1)
        return 1;

    v2 = vertex_init();
    if (!v2)
        return 1;

    /*El primero tendrá id 10, tag one y estado WHITE.*/
    vertex_setId(v1, 10);
    vertex_setTag(v1, "one");
    vertex_setState(v1, WHITE);

    /*El segundo tendrá id 20, tag two y estado BLACK.*/
    vertex_setId(v2, 20);
    vertex_setTag(v2, "two");
    vertex_setState(v2, BLACK);

    /*Imprimir ambos vértices y después un salto de línea.*/

    vertex_print(stdout, v1);
    vertex_print(stdout, v2);
    fprintf(stdout, "\n");

    /*Comparar ambos vértices y mostrar un mensaje que diga el resultado.*/

    cmp = vertex_cmp(v1, v2);
    printf("Equals? ");

    if (cmp == 0)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }

    /* Imprimir el tag del segundo vértice.*/

    printf("Vertex 2 tag: %s\n", vertex_getTag(v2));

    /* Copiar el primer vértice en un tercero.*/
    v3 = vertex_copy(v1);
    
    /*Imprimir el id del tercer vértice.*/
    printf("Vertex 3 id: %ld\n", vertex_getId(v3));
    /*Imprimir el primer y el tercer vértice y después un salto de línea.*/
    vertex_print(stdout, v1);
    vertex_print(stdout, v3);
    fprintf(stdout, "\n");

    /*Comparar el primer y tercer vértices y mostrar un mensaje que diga el resultado.*/
    cmp = vertex_cmp(v1, v3);
    printf("Equals? ");

    if (cmp == 0)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    
    /*Liberar memoria.*/
    vertex_free(v1);
    vertex_free(v2);
    vertex_free(v3);

    return 0;
}