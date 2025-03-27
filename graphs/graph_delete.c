#include "graphs.h"
#include <stdlib.h>

/**
 * free_edges - Free all edges of a vertex
 * @edges: Pointer to the head of edges linked list
 */
void free_edges(edge_t *edges)
{
    edge_t *tmp;

    while (edges)
    {
        tmp = edges;
        edges = edges->next;
        free(tmp);
    }
}

/**
 * graph_delete - Deletes a graph
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
    vertex_t *vertex, *tmp;

    if (!graph)
        return;

    vertex = graph->vertices;
    while (vertex)
    {
        tmp = vertex;
        vertex = vertex->next;
        
        /* Free the content string */
        if (tmp->content)
            free(tmp->content);
        
        /* Free all edges */
        free_edges(tmp->edges);
        
        /* Free the vertex itself */
        free(tmp);
    }

    /* Free the graph structure */
    free(graph);
}

