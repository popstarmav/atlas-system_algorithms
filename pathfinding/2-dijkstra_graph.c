#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graphs.h"
#include "pathfinding.h"
#include "queues.h"

/**
 * create_point - Creates a new point and adds it to the path
 * @x: x-coordinate
 * @y: y-coordinate
 * @path: Queue to store the path
 * Return: 1 on success, 0 on failure
 */
static int create_point(int x, int y, queue_t *path)
{
	point_t *point = malloc(sizeof(point_t));

	if (!point)
		return (0);
	point->x = x;
	point->y = y;

	if (queue_push_front(path, point) == NULL)
	{
		free(point);
		return (0);
	}

	return (1);
}

/**
 * build_path - Builds the path from start to target
 * @target: Target vertex
 * Return: Queue containing the path
 */
static queue_t *build_path(vertex_t const *target)
{
	queue_t *path;
	vertex_t *current;

	path = queue_create();
	if (!path)
		return (NULL);

	current = (vertex_t *)target;

	while (current)
	{
		if (!create_point(current->x, current->y, path))
		{
			queue_delete(path);
			return (NULL);
		}

		/* Move to the previous vertex in the path */
		current = (vertex_t *)current->content;

		/* Break if we've reached a vertex with no previous (start) */
		if (current && current->content == NULL)
		{
			create_point(current->x, current->y, path);
			break;
		}
	}

	return (path);
}

/**
 * process_vertex - Processes a vertex in Dijkstra's algorithm
 * @current: Current vertex to process
 * @queue: Priority queue
 * @target: Target vertex
 * Return: 1 if target reached, 0 otherwise
 */
static int process_vertex(vertex_t *current, queue_t *queue, vertex_t *target)
{
	edge_t *edge;
	size_t new_distance;

	printf("Checking %s, distance from start is %lu\n",
		(char *)current->content, current->index);

	if (current == target)
		return (1);

	/* Mark as visited by setting a flag */
	current->content = (void *)1;

	/* Process all neighbors */
	for (edge = current->edges; edge; edge = edge->next)
	{
		/* Skip if already visited */
		if (edge->dest->content != NULL && edge->dest->content == (void *)1)
			continue;

		new_distance = current->index + edge->weight;

		if (new_distance < edge->dest->index)
		{
			edge->dest->index = new_distance;
			/* Store previous vertex pointer in content temporarily */
			edge->dest->content = (void *)current;
			queue_push_back(queue, edge->dest);
		}
	}

	return (0);
}

/**
 * initialize_algorithm - Initializes vertices and creates queue
 * @graph: Graph to process
 * @start: Starting vertex
 * @target: Target vertex
 * @queue: Pointer to store created queue
 * Return: Pointer to target vertex in graph, NULL on failure
 */
static vertex_t *initialize_algorithm(graph_t *graph, vertex_t const *start,
				vertex_t const *target, queue_t **queue)
{
	vertex_t *vertex, *start_vertex = NULL, *target_vertex = NULL;

	/* Initialize all vertices */
	for (vertex = graph->vertices; vertex; vertex = vertex->next)
	{
		vertex->index = UINT_MAX;
		vertex->content = NULL;

		if (vertex->x == start->x && vertex->y == start->y)
			start_vertex = vertex;

		if (vertex->x == target->x && vertex->y == target->y)
			target_vertex = vertex;
	}

	if (!start_vertex || !target_vertex)
		return (NULL);

	/* Set start vertex distance to 0 */
	start_vertex->index = 0;

	/* Create priority queue */
	*queue = queue_create();
	if (!*queue)
		return (NULL);

	/* Add start vertex to queue */
	if (queue_push_back(*queue, start_vertex) == NULL)
	{
		queue_delete(*queue);
		return (NULL);
	}

	return (target_vertex);
}

/**
 * dijkstra_graph - Finds the shortest path between two points in a graph
 * @graph: Pointer to the graph
 * @start: Pointer to the starting vertex
 * @target: Pointer to the target vertex
 * Return: Queue containing the path from start to target
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	queue_t *queue;
	vertex_t *current, *target_vertex;
	int target_reached = 0;
	queue_t *path;

	if (!graph || !start || !target)
		return (NULL);

	target_vertex = initialize_algorithm(graph, start, target, &queue);
	if (!target_vertex || !queue)
		return (NULL);

	/* Main Dijkstra algorithm loop */
	while ((current = dequeue(queue)) != NULL)
	{
		target_reached = process_vertex(current, queue, target_vertex);
		if (target_reached)
			break;
	}

	/* No path found */
	if (target_vertex->content == NULL && target_vertex != current)
	{
		queue_delete(queue);
		return (NULL);
	}

	path = build_path(target_vertex);
	queue_delete(queue);
	return (path);
}
