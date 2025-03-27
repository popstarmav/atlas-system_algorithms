#include "graphs.h"
#include <stdlib.h>

/**
 * free_edges - Frees all edges of a vertex
 * @edges: Pointer to the first edge in the list
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
 * free_vertices - Frees all vertices in the graph
 * @vertices: Pointer to the first vertex in the list
 */
void free_vertices(vertex_t *vertices)
{
	vertex_t *tmp;

	while (vertices)
	{
		tmp = vertices;
		vertices = vertices->next;
		free_edges(tmp->edges);
		free(tmp->content);
		free(tmp);
	}
}

/**
 * graph_delete - Completely deletes a graph
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
	if (!graph)
		return;

	free_vertices(graph->vertices);
	free(graph);
}
