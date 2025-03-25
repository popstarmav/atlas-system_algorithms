#include "graphs.h"
#include <stdio.h>

/**
 * graph_display - Prints the adjacency list of the graph
 * @graph: Pointer to the graph to display
 */
void graph_display(const graph_t *graph)
{
    vertex_t *vertex;
    edge_t *edge;
    size_t i;

    if (!graph)
        return;

    printf("Number of vertices: %lu\n", graph->nb_vertices);
    
    vertex = graph->vertices;
    while (vertex)
    {
        printf("[%lu] %s\n", vertex->index, vertex->content);
        
        /* Display edges if needed */
        edge = vertex->edges;
        i = 0;
        while (edge)
        {
            printf("\t-> %s\n", edge->dest->content);
            edge = edge->next;
            i++;
        }
        
        vertex = vertex->next;
    }
}
