#include <stdio.h>
#include <stdlib.h>
#include "delivery.h"
#include "vertex.h"

#define MAX_C 1024

/**
* @brief Builds a delivery from the information read on the file.
*
* @param pf File descriptor. The file should contains the following
information:
* Firt line: delivery_name product_name
* Second line: number of cities/vertices
* Following lines: vertices description
*
* @return A pointer to the fullfilled delivery. If there have been
errors returns NULL.
*/
Delivery *build_delivery(FILE *pf);

Delivery *build_delivery(FILE *pf)
{
    int i, num_prod;
    char comunidad[MAX_C], prod[MAX_C], descr[MAX_C];
    Delivery *d = NULL;
    Vertex *v = NULL;

    if (!pf)
        return NULL;

    fscanf(pf, "%s %s", comunidad, prod);
    fscanf(pf, "%d", &num_prod);

    d = delivery_init(comunidad, prod);
    if (!d)
        return NULL;

    fgetc(pf);
    for (i = 0; i < num_prod; i++)
    {
        fgets(descr, MAX_C, pf);
        v = vertex_initFromString(descr);
        delivery_add(stdout, d, v, vertex_print);
    }

    return d;
}

int main(int argc, char *argv[])
{
    Delivery *d = NULL;
    FILE *f = NULL;
    if (argc != 2)
    {
        fprintf(stderr, "Numero de argumentos incorrecto\n");
        return -1;
    }

    f = fopen(argv[1], "r");
    if (!f)
        return -1;

    d = build_delivery(f);
    if (!d)
    {
        fclose(f);
        return -1;
    }

    delivery_run_plan(stdout, d, vertex_print, delivery_free);

    fclose(f);

    return 0;
}