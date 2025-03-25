#include "graphs.h"
#include <stdlib.h>
#include <string.h>

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
	vertex_t *src_vertex = NULL, *dest_vertex = NULL;
	vertex_t *tmp = NULL;
	edge_t *new_edge = NULL, *edge = NULL;

	if (!graph || !src || !dest)
		return (0);

	/* Find source and destination vertices */
	tmp = graph->vertices;
	while (tmp)
	{
		if (strcmp(tmp->content, src) == 0)
			src_vertex = tmp;
		if (strcmp(tmp->content, dest) == 0)
			dest_vertex = tmp;
		tmp = tmp->next;
	}
	if (!src_vertex || !dest_vertex)
		return (0);

	/* Check if edge already exists */
	edge = src_vertex->edges;
	while (edge)
	{
		if (edge->dest == dest_vertex)
			break;
		edge = edge->next;
	}
	if (!edge)
	{
		/* Add edge from source to destination at the end of the list */
		new_edge = malloc(sizeof(edge_t));
		if (!new_edge)
			return (0);
		new_edge->dest = dest_vertex;
		new_edge->next = NULL;

		if (!src_vertex->edges)
			src_vertex->edges = new_edge;
		else
		{
			edge = src_vertex->edges;
			while (edge->next)
				edge = edge->next;
			edge->next = new_edge;
		}
		src_vertex->nb_edges++;
	}

	/* If bidirectional, add edge from destination to source */
	if (type == BIDIRECTIONAL)
	{
		/* Check if reverse edge already exists */
		edge = dest_vertex->edges;
		while (edge)
		{
			if (edge->dest == src_vertex)
				break;
			edge = edge->next;
		}
		if (!edge)
		{
			/* Add edge from destination to source at the end of the list */
			new_edge = malloc(sizeof(edge_t));
			if (!new_edge)
				return (0);
			new_edge->dest = src_vertex;
			new_edge->next = NULL;

			if (!dest_vertex->edges)
				dest_vertex->edges = new_edge;
			else
			{
				edge = dest_vertex->edges;
				while (edge->next)
					edge = edge->next;
				edge->next = new_edge;
			}
			dest_vertex->nb_edges++;
		}
	}

	return (1);
}

