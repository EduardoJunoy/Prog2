#include <string.h>

#include "graph.h"
#include "stack.h"
#include "queue.h"

#define MAX_VTX 4096

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

/* START [Private_functions] */
int _graph_findVertexByTag(const Graph *, char *tag);
Status _graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx);
int _graph_getNumConnections(const Graph *g, int ix);
long *_graph_getConnections(const Graph *g, int ix);
void _graph_setVertexState(Graph *g, Label l);
Vertex *_graph_getVertexById(const Graph *g, long id);
/* END [Private_functions] */

Status graph_breathSearch(Graph *g, long from_id, long to_id)
{
    Queue *q = NULL;
    Vertex *vf = NULL, *vt = NULL, *vo = NULL, *v = NULL;
    int i, numc_vo = 0;
    long *arr = NULL;

    if (!g)
        return ERROR;

    _graph_setVertexState(g, WHITE);

    q = queue_new();
    if (!q)
        return ERROR;

    vf = _graph_getVertexById(g, from_id);
    if (!vf)
    {
        queue_free(q);
        return ERROR;
    }

    vt = _graph_getVertexById(g, to_id);
    if (!vt)
    {
        queue_free(q);
        return ERROR;
    }

    if (queue_push(q, vf) == ERROR)
    {
        queue_free(q);
        return ERROR;
    }

    while (queue_isEmpty(q) == FALSE)
    {
        vo = queue_pop(q);
        if (!vo)
        {
            queue_free(q);
            return ERROR;
        }

        if (vertex_cmp(vo, vt) == 0)
        {
            if (vertex_setState(vt, BLACK) == ERROR)
            {
                queue_free(q);
                return ERROR;
            }

            vertex_print(stdout, vo);
            fprintf(stdout, "\n");
            break;
        }

        else
        {
            if (vertex_getState(vo) == WHITE)
            {
                if (vertex_setState(vo, BLACK) == ERROR)
                {
                    queue_free(q);
                    return ERROR;
                }

                vertex_print(stdout, vo);
                fprintf(stdout, "\n");

                numc_vo = _graph_getNumConnections(g, vertex_getIndex(vo));
                arr = _graph_getConnections(g, vertex_getIndex(vo));

                for (i = 0; i < numc_vo; i++)
                {
                    v = _graph_getVertexById(g, arr[i]);
                    if (vertex_getState(v) == WHITE)
                    {
                        if (queue_push(q, v) == ERROR)
                        {
                            queue_free(q);
                            free(arr);
                            return ERROR;
                        }
                    }
                }

                free(arr);
            }
        }
    }

    queue_free(q);
    return OK;
}

/**
 * @brief: Makes a search from the origin vertex to the destination vertex
of a graph using the depth-first search algorithm
 * using an ADT Stack
 *
 * The function prints each visited vertex while traversing the graph
 *
 * @param g, Pointer to graph
 * @param from_id, id of the origin Vertex
 * @param to_id, id of the destination Vertex
 * @return The function returns OK or ERROR
**/
Status graph_depthSearch(Graph *g, long from_id, long to_id)
{
    Stack *s = NULL;
    Vertex *vf = NULL, *vt = NULL, *vo = NULL, *v = NULL;
    int i, numc_vo = 0;
    long *arr = NULL;

    if (!g)
        return ERROR;

    _graph_setVertexState(g, WHITE);

    s = stack_init();
    if (!s)
        return ERROR;

    vf = _graph_getVertexById(g, from_id);
    if (!vf)
    {
        stack_free(s);
        return ERROR;
    }

    vt = _graph_getVertexById(g, to_id);
    if (!vt)
    {
        stack_free(s);
        return ERROR;
    }

    if (stack_push(s, vf) == ERROR)
    {
        stack_free(s);
        return ERROR;
    }

    while (stack_isEmpty(s) == FALSE)
    {
        vo = stack_pop(s);
        if (!vo)
        {
            stack_free(s);
            return ERROR;
        }

        if (vertex_cmp(vo, vt) == 0)
        {
            if (vertex_setState(vt, BLACK) == ERROR)
            {
                stack_free(s);
                return ERROR;
            }

            vertex_print(stdout, vo);
            fprintf(stdout, "\n");
            break;
        }

        else
        {
            if (vertex_getState(vo) == WHITE)
            {
                if (vertex_setState(vo, BLACK) == ERROR)
                {
                    stack_free(s);
                    return ERROR;
                }

                vertex_print(stdout, vo);
                fprintf(stdout, "\n");

                numc_vo = _graph_getNumConnections(g, vertex_getIndex(vo));
                arr = _graph_getConnections(g, vertex_getIndex(vo));

                for (i = 0; i < numc_vo; i++)
                {
                    v = _graph_getVertexById(g, arr[i]);
                    if (vertex_getState(v) == WHITE)
                    {
                        if (stack_push(s, v) == ERROR)
                        {
                            stack_free(s);
                            free(arr);
                            return ERROR;
                        }
                    }
                }

                free(arr);
            }
        }
    }

    stack_free(s);
    return OK;
}

Vertex *_graph_getVertexById(const Graph *g, long id)
{
    int i;

    if (!g)
        return NULL; //

    for (i = 0; i < g->num_vertices; i++)
    {
        if (id == vertex_getId(g->vertices[i]))
            return g->vertices[i];
    }

    return NULL;
}

// devuelve -1 si falla, 0 si no ha encontrado el vertice y 1 si lo ha encontrado
int _graph_findVertexByTag(const Graph *g, char *tag)
{
    int i;

    if (!g || !tag)
        return -1;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
            return 1;
    }

    return 0;
}

Status _graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx)
{
    if (!g)
        return ERROR; // Modificar

    g->connections[origIx][destIx] = TRUE; // Quizas hay que comprobar si origIx y destIx pertenecen al grafo primero
    g->num_edges++;
    return OK;
}

int _graph_getNumConnections(const Graph *g, int ix)
{
    int i, count;

    if (!g)
        return -1; //

    for (i = count = 0; i < g->num_vertices; i++)
    {
        if (g->connections[ix][i] == TRUE)
            count++;
    }

    return count;
}

long *_graph_getConnections(const Graph *g, int ix)
{
    int i, k;
    long *arr = NULL;

    if (!g)
        return NULL; //

    arr = (long *)malloc(_graph_getNumConnections(g, ix) * sizeof(long));
    if (!arr)
        return NULL;

    for (i = k = 0; i < g->num_vertices; i++)
    {
        if (g->connections[ix][i] == TRUE)
        {
            arr[k] = vertex_getId(g->vertices[i]);
            k++;
        }
    }

    return arr;
}

void _graph_setVertexState(Graph *g, Label l)
{
    int i;
    if (!g)
        return;

    for (i = 0; i < g->num_vertices; i++)
        if (vertex_setState(g->vertices[i], l) == ERROR)
            return;

    return;
}

Graph *graph_init()
{
    Graph *g = NULL;
    int i, j;

    g = (Graph *)malloc(sizeof(Graph));
    if (!g)
    {
        return NULL;
    }
    for (i = 0; i < MAX_VTX; i++)
    {
        g->vertices[i] = NULL;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        for (j = 0; j < MAX_VTX; j++)
        {
            g->connections[i][j] = FALSE;
        }
    }

    g->num_vertices = 0;
    g->num_edges = 0;

    return g;
}

void graph_free(Graph *g)
{
    int i;
    for (i = 0; i < g->num_vertices; i++)
        vertex_free(g->vertices[i]);

    free(g);
}

/**
 * @brief Inserts a new vertex in a graph.
 *
 * Creates a vertex by calling vertex_initFromString and adds it to
 * a graph. If a vertex with the same id already exists in the graph,
 * it is not added.
 *
 * @param g Pointer to the graph.
 * @param desc Description of the vertex.
 *
 * @return Returns OK if the vertex could be created (or if it exists
 * already), ERROR otherwise.
 **/
Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *v = NULL;

    if (!g || !desc)
        return ERROR;

    v = vertex_initFromString(desc);
    if (!v)
        return ERROR;

    if (graph_contains(g, vertex_getId(v)) == TRUE)
    {
        vertex_free(v);
        return ERROR;
    }

    vertex_setIndex(v, g->num_vertices);
    g->vertices[g->num_vertices] = v;
    g->num_vertices++;

    return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest)
{
    int i, pos_o, pos_d, count = 0;

    if (!g || !orig || !dest)
    {
        return ERROR;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (count == 2)
            break;

        if (orig == vertex_getId(g->vertices[i]))
        {
            pos_o = i;
            count++;
        }

        if (dest == vertex_getId(g->vertices[i]))
        {
            pos_d = i;
            count++;
        }
    }

    if (count == 2)
    {
        g->connections[pos_o][pos_d] = TRUE;
        g->num_edges++;
        return OK;
    }

    return ERROR;
}

Bool graph_contains(const Graph *g, long id)
{
    int i;
    long id_g;

    if (!g || id == -1)
        return FALSE;

    for (i = 0; i < g->num_vertices; i++)
    {
        id_g = vertex_getId(g->vertices[i]);
        if (id == id_g)
            return TRUE;
    }

    return FALSE;
}

int graph_getNumberOfVertices(const Graph *g)
{
    if (!g)
    {
        return -1;
    }
    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g)
{
    if (!g)
    {
        return -1;
    }
    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    int i, pos_o, pos_d, count = 0;

    if (!g || orig == -1 || dest == -1)
    {
        return FALSE;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (count == 2)
            break;

        if (orig == vertex_getId(g->vertices[i]))
        {
            pos_o = i;
            count++;
        }

        if (dest == vertex_getId(g->vertices[i]))
        {
            pos_d = i;
            count++;
        }
    }

    if (g->connections[pos_o][pos_d] == TRUE)
        return TRUE;

    return FALSE;
}

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns the total number of connections starting at
 * vertex with ID id, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int i, pos, count;

    if (!g || !id)
        return -1;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (id == vertex_getId(g->vertices[i]))
        {
            pos = i;
            break;
        }
    }

    for (i = count = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
            count++;
    }

    return count;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{
    int i, k, pos;
    long *arr = NULL;

    if (!g || id == -1)
        return NULL;

    arr = (long *)malloc(graph_getNumberOfConnectionsFromId(g, id) * sizeof(long));
    if (!arr)
        return NULL;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (id == vertex_getId(g->vertices[i]))
        {
            pos = i;
            break;
        }
    }

    for (i = 0, k = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
        {
            arr[k] = vertex_getId(g->vertices[i]);
            k++;
        }
    }

    return arr;
}

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns the total number of connections starting at
 * vertex with Tag tag, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i, pos, count;

    if (!g || !tag)
        return -1;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(tag, vertex_getTag(g->vertices[i])) == 0)
        {
            pos = i;
            break;
        }
    }
    for (i = count = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
            count++;
    }

    return count;
}

/**
 * @brief Returns an array with the ids of all the vertices which a
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which
 * the vertex with Tag tag is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int i, k, pos;
    long *arr = NULL;

    if (!g || !tag)
        return NULL;

    arr = (long *)malloc(graph_getNumberOfConnectionsFromTag(g, tag) * sizeof(long));
    if (!arr)
        return NULL;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(tag, vertex_getTag(g->vertices[i])) == 0)
        {
            pos = i;
            break;
        }
    }

    for (i = 0, k = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
        {
            arr[k] = vertex_getId(g->vertices[i]);
            k++;
        }
    }
    return arr;
}

/**
 * @brief Prints a graph.
 *
 * Prints the graph g to the file pf.
 * The format to be followed is: print a line by vertex with the
 * information associated with the vertex and the id of their connections:
 *
 * For example:
 * [1, Madrid, 0]: [2, Toledo, 0] [3, Avila, 0]
 * [2, Toledo, 0]: [4, Segovia, 0]
 * [3, Avila, 0]:
 * [4, Segovia, 0]: [3, Avila, 0]
 *
 * @param pf File descriptor.
 * @param g Pointer to the graph.
 *
 * @return The number of characters printed, or -1 if there is any error.
 */
int graph_print(FILE *pf, const Graph *g)
{
    int i, j, k, num_print = 0;
    long *arr, v_id;

    if (!pf || !g)
        return -1;

    for (i = 0; i < g->num_vertices; i++)
    {
        num_print += vertex_print(pf, g->vertices[i]);
        fprintf(pf, ": ");

        v_id = vertex_getId(g->vertices[i]);
        arr = graph_getConnectionsFromId(g, v_id);

        for (j = 0, k = 0; k < graph_getNumberOfConnectionsFromId(g, v_id); j++)
        {
            if (arr[k] == vertex_getId(g->vertices[j]))
            {
                num_print += vertex_print(pf, g->vertices[j]);
                k++;
            }
        }
        num_print += fprintf(pf, "\n");
        free(arr);
    }

    return num_print;
}

/**
 * @brief Reads a graph definition from a text file.
 *
 * Reads a graph description from the text file pointed to by fin,
 * and fills the graph g.
 *
 * The first line in the file contains the number of vertices.
 * Then one line per vertex with the vertex description.
 * Finally one line per connection, with the ids of the origin and
 * the destination.
 *
 * For example:
 *
 * 4
 * id:1 tag:Madrid
 * id:2 tag:Toledo
 * id:3 tag:Avila
 * id:4 tag:Segovia
 * 1 2
 * 1 3
 * 2 4
 * 4 3
 *
 * @param fin Pointer to the input stream.
 * @param g Pointer to the graph.
 *
 * @return OK or ERROR
 */
Status graph_readFromFile(FILE *fin, Graph *g)
{
    int i;
    int num_vertices;
    long orig, dest;
    char desc[1024];

    if (!fin)
        return ERROR;

    fscanf(fin, "%d", &num_vertices);
    fgetc(fin);

    for (i = 0; i < num_vertices; i++)
    {
        fgets(desc, 1024, fin);
        graph_newVertex(g, desc);
    }

    while (fscanf(fin, "%ld %ld", &orig, &dest) != EOF)
        graph_newEdge(g, orig, dest);

    return OK;
}