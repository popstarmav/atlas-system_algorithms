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
 * @prev_map: Map of previous vertices
 * @vertex_count: Number of vertices in the graph
 * Return: Queue containing the path
 */
static queue_t *build_path(vertex_t const *target, vertex_t **prev_map,
			size_t vertex_count)
{
	queue_t *path;
	vertex_t *current;
	size_t i;

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

		/* Find the previous vertex in the map */
		for (i = 0; i < vertex_count; i++)
		{
			if (prev_map[i * 2] == current)
			{
				current = prev_map[i * 2 + 1];
				break;
			}
		}

		/* If no previous vertex found, we've reached the start */
		if (i == vertex_count)
			break;
	}

	return (path);
}

/**
 * process_vertex - Processes a vertex in Dijkstra's algorithm
 * @current: Current vertex to process
 * @queue: Priority queue
 * @target: Target vertex
 * @prev_map: Map of previous vertices
 * @vertex_count: Pointer to the number of vertices processed
 * Return: 1 if target reached, 0 otherwise
 */
static int process_vertex(vertex_t *current, queue_t *queue, vertex_t *target,
			vertex_t **prev_map, size_t *vertex_count)
{
	edge_t *edge;
	size_t new_distance;

	printf("Checking %s, distance from start is %lu\n",
		(char *)current->content, current->index);

	if (current == target)
		return (1);

	/* Process all neighbors */
	for (edge = current->edges; edge; edge = edge->next)
	{
		/* Skip if already processed with a shorter path */
		if (edge->dest->index != UINT_MAX &&
			edge->dest->index <= current->index + edge->weight)
			continue;

		new_distance = current->index + edge->weight;
		
		/* If this is a better path, update the distance and previous vertex */
		if (new_distance < edge->dest->index)
		{
			edge->dest->index = new_distance;
			
			/* Store the previous vertex in the map */
			prev_map[*vertex_count * 2] = edge->dest;
			prev_map[*vertex_count * 2 + 1] = current;
			(*vertex_count)++;
			
			queue_push_back(queue, edge->dest);
		}
	}

	return (0);
}

/**
 * count_vertices - Counts the number of vertices in a graph
 * @graph: The graph to count vertices in
 * Return: Number of vertices
 */
static size_t count_vertices(graph_t *graph)
{
	size_t count = 0;
	vertex_t *vertex;

	for (vertex = graph->vertices; vertex; vertex = vertex->next)
		count++;

	return (count);
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
	queue_t *queue, *path = NULL;
	vertex_t *current, *target_vertex = NULL, *start_vertex = NULL;
	vertex_t **prev_map;
	size_t vertex_count = 0, max_vertices;
	int target_reached = 0;

	if (!graph || !start || !target)
		return (NULL);

	/* Find start and target vertices in the graph */
	for (current = graph->vertices; current; current = current->next)
	{
		current->index = UINT_MAX;
		if (current->x == start->x && current->y == start->y)
			start_vertex = current;
		if (current->x == target->x && current->y == target->y)
			target_vertex = current;
	}

	if (!start_vertex || !target_vertex)
		return (NULL);

	/* Create map for previous vertices */
	max_vertices = count_vertices(graph);
	prev_map = malloc(max_vertices * 2 * sizeof(vertex_t *));
	if (!prev_map)
		return (NULL);

	/* Initialize start vertex and queue */
	start_vertex->index = 0;
	queue = queue_create();
	if (!queue)
	{
		free(prev_map);
		return (NULL);
	}

	if (queue_push_back(queue, start_vertex) == NULL)
	{
		queue_delete(queue);
		free(prev_map);
		return (NULL);
	}

	/* Main Dijkstra algorithm loop */
	while ((current = dequeue(queue)) != NULL)
	{
		target_reached = process_vertex(current, queue, target_vertex,
						prev_map, &vertex_count);
		if (target_reached)
			break;
	}

	/* Build path if target was reached */
	if (target_vertex->index != UINT_MAX)
		path = build_path(target_vertex, prev_map, vertex_count);

	/* Print path */
	if (path)
	{
		point_t *point;
		queue_t *path_copy = queue_create();
		
		printf("Path found: ");
		while ((point = dequeue(path)) != NULL)
		{
			for (current = graph->vertices; current; current = current->next)
			{
				if (current->x == point->x && current->y == point->y)
				{
					printf("%s ", (char *)current->content);
					break;
				}
			}
			
			/* Save the point for the return value */
			queue_push_back(path_copy, point);
		}
		printf("\n");
		
		/* Restore the path for return */
		while ((point = dequeue(path_copy)) != NULL)
			queue_push_back(path, point);
		
		queue_delete(path_copy);
	}

	queue_delete(queue);
	free(prev_map);
	return (path);
}

