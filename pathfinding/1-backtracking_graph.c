#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathfinding.h"

/* Forward declaration */
static int backtrack_graph(vertex_t const *current, vertex_t const *target,
		queue_t *visited, queue_t *path);

/**
 * is_vertex_visited - Checks if a vertex has been visited
 * @visited: Queue of visited vertices
 * @vertex: Vertex to check
 * Return: 1 if visited, 0 otherwise
 */
static int is_vertex_visited(queue_t *visited, vertex_t const *vertex)
{
	queue_node_t *node;

	for (node = visited->front; node; node = node->next)
	{
		if (strcmp((char *)node->ptr, (char *)vertex->content) == 0)
			return (1);
	}
	return (0);
}

/**
 * mark_visited - Marks a vertex as visited
 * @visited: Queue of visited vertices
 * @vertex: Vertex to mark
 * Return: 1 on success, 0 on failure
 */
static int mark_visited(queue_t *visited, vertex_t const *vertex)
{
	char *vertex_name = strdup((char *)vertex->content);

	if (!vertex_name)
		return (0);

	if (queue_push_back(visited, vertex_name) == NULL)
	{
		free(vertex_name);
		return (0);
	}
	return (1);
}

/**
 * add_to_path - Adds a vertex to the path
 * @path: Queue to store the path
 * @vertex: Vertex to add
 * Return: 1 on success, 0 on failure
 */
static int add_to_path(queue_t *path, vertex_t const *vertex)
{
	char *vertex_name = strdup((char *)vertex->content);

	if (!vertex_name)
		return (0);

	if (queue_push_front(path, vertex_name) == NULL)
	{
		free(vertex_name);
		return (0);
	}
	return (1);
}

/**
 * clean_visited_queue - Frees the visited queue
 * @visited: Queue to free
 */
static void clean_visited_queue(queue_t *visited)
{
	while (visited->front)
		free(dequeue(visited));
	queue_delete(visited);
}

/**
 * handle_same_vertex - Handles case when start and target are the same
 * @start: Starting vertex
 * Return: Queue with the single vertex, or NULL on failure
 */
static queue_t *handle_same_vertex(vertex_t const *start)
{
	queue_t *path = queue_create();

	if (!path)
		return (NULL);

	if (!add_to_path(path, start))
	{
		queue_delete(path);
		return (NULL);
	}
	return (path);
}

/**
 * backtrack_graph_helper - Helper for backtracking algorithm
 * @current: Current vertex
 * @target: Target vertex
 * @visited: Queue of visited vertices
 * @path: Queue to store the path
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack_graph_helper(vertex_t const *current,
		vertex_t const *target, queue_t *visited, queue_t *path)
{
	edge_t *edge;

	/* Explore all adjacent vertices */
	for (edge = current->edges; edge; edge = edge->next)
	{
		/* Skip visited vertices */
		if (is_vertex_visited(visited, edge->dest))
			continue;

		/* Recursively explore the adjacent vertex */
		if (backtrack_graph(edge->dest, target, visited, path))
		{
			/* If path found, add current vertex to path */
			if (!add_to_path(path, current))
				return (0);
			return (1);
		}
	}

	/* No path found from this vertex */
	return (0);
}

/**
 * backtrack_graph - Recursive backtracking function to find path in graph
 * @current: Current vertex being explored
 * @target: Target vertex to reach
 * @visited: Queue to track visited vertices
 * @path: Queue to store the path
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack_graph(vertex_t const *current, vertex_t const *target,
		queue_t *visited, queue_t *path)
{
	/* Print current vertex being checked */
	printf("Checking %s\n", (char *)current->content);

	/* If target is reached, add current vertex to path and return success */
	if (current == target)
	{
		if (!add_to_path(path, current))
			return (0);
		return (1);
	}

	/* Mark current vertex as visited */
	if (!mark_visited(visited, current))
		return (0);

	/* Continue exploring adjacent vertices */
	return (backtrack_graph_helper(current, target, visited, path));
}

/**
 * backtracking_graph - Searches for path from start to target in a graph
 * @graph: Pointer to the graph to go through
 * @start: Pointer to the starting vertex
 * @target: Pointer to the target vertex
 * Return: Queue containing the path, or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	queue_t *path;
	queue_t *visited;
	int success = 0;

	/* Check for invalid inputs */
	if (!graph || !start || !target)
		return (NULL);

	/* If start and target are the same, return a path with just the start */
	if (start == target)
		return (handle_same_vertex(start));

	/* Create queues for path and visited vertices */
	path = queue_create();
	if (!path)
		return (NULL);

	visited = queue_create();
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}

	/* Start backtracking from the start vertex */
	success = backtrack_graph(start, target, visited, path);

	/* Clean up visited queue */
	clean_visited_queue(visited);

	/* If no path found, delete the queue and return NULL */
	if (!success)
	{
		queue_delete(path);
		return (NULL);
	}

	return (path);
}

