#include "graphs.h"
#include <stdlib.h>

/**
 * graph_create - Creates a new graph
 *
 * Return: Pointer to the created graph, or NULL on failure
 */
graph_t *graph_create(void)
{
    graph_t *graph;

    graph = malloc(sizeof(graph_t));
    if (!graph)
        return (NULL);

    graph->nb_vertices = 0;
    graph->vertices = NULL;

    return (graph);
}

