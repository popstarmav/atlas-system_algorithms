#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * find_vertex - Finds a vertex in the graph by content
 * @graph: Pointer to the graph
 * @content: String to search for
 *
 * Return: Pointer to the vertex if found, NULL otherwise
 */
vertex_t *find_vertex(const graph_t *graph, const char *content)
{
	vertex_t *vertex;

	if (!graph || !content)
		return (NULL);

	vertex = graph->vertices;
	while (vertex)
	{
		if (strcmp(vertex->content, content) == 0)
			return (vertex);
		vertex = vertex->next;
	}
	return (NULL);
}

/**
 * add_edge_to_vertex - Adds an edge from one vertex to another
 * @src: Source vertex
 * @dest: Destination vertex
 *
 * Return: 1 on success, 0 on failure
 */
int add_edge_to_vertex(vertex_t *src, vertex_t *dest)
{
	edge_t *new_edge, *edge;

	/* Check if edge already exists */
	edge = src->edges;
	while (edge)
	{
		if (edge->dest == dest)
			return (1); /* Edge already exists */
		edge = edge->next;
	}

	/* Create new edge */
	new_edge = malloc(sizeof(edge_t));
	if (!new_edge)
		return (0);

	new_edge->dest = dest;
	new_edge->next = src->edges;
	src->edges = new_edge;
	src->nb_edges++;

	return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices to an existing graph
 * @graph: Pointer to the graph to add the edge to
 * @src: String identifying the vertex to make the connection from
 * @dest: String identifying the vertex to connect to
 * @type: Type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		edge_type_t type)
{
	vertex_t *src_vertex, *dest_vertex;

	if (!graph || !src || !dest)
		return (0);

	/* Find source and destination vertices */
	src_vertex = find_vertex(graph, src);
	dest_vertex = find_vertex(graph, dest);
	if (!src_vertex || !dest_vertex)
		return (0);

	/* Add edge from source to destination */
	if (!add_edge_to_vertex(src_vertex, dest_vertex))
		return (0);

	/* If bidirectional, add edge from destination to source */
	if (type == BIDIRECTIONAL)
	{
		if (!add_edge_to_vertex(dest_vertex, src_vertex))
		{
			/* Remove the edge we just added (cleanup) */
			edge_t *edge = src_vertex->edges;
			src_vertex->edges = edge->next;
			src_vertex->nb_edges--;
			free(edge);
			return (0);
		}
	}

	return (1);
}

