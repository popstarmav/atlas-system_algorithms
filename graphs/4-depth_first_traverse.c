#include "graphs.h"
#include <stdlib.h>

/**
 * dfs_helper - Helper function for depth-first traversal
 * @vertex: Current vertex being visited
 * @visited: Array to track visited vertices
 * @depth: Current depth in the traversal
 * @max_depth: Pointer to track maximum depth reached
 * @action: Function to call for each visited vertex
 * Return: void
 */
void dfs_helper(const vertex_t *vertex, int *visited, size_t depth,
                size_t *max_depth, void (*action)(const vertex_t *v, size_t depth))
{
    edge_t *edge;

    if (!vertex || visited[vertex->index])
        return;

    /* Mark vertex as visited */
    visited[vertex->index] = 1;

    /* Call action function on the vertex */
    action(vertex, depth);

    /* Update max depth if current depth is greater */
    if (depth > *max_depth)
        *max_depth = depth;

    /* Traverse all adjacent vertices */
    edge = vertex->edges;
    while (edge)
    {
        if (!visited[edge->dest->index])
            dfs_helper(edge->dest, visited, depth + 1, max_depth, action);
        edge = edge->next;
    }
}

/**
 * depth_first_traverse - Traverses a graph using depth-first algorithm
 * @graph: Pointer to the graph to traverse
 * @action: Function to call for each visited vertex
 * Return: The maximum depth reached, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
    int *visited;
    size_t max_depth = 0;
    size_t i;

    /* Check for valid inputs */
    if (!graph || !action || !graph->vertices)
        return (0);

    /* Allocate and initialize visited array */
    visited = malloc(sizeof(int) * graph->nb_vertices);
    if (!visited)
        return (0);

    for (i = 0; i < graph->nb_vertices; i++)
        visited[i] = 0;

    /* Start DFS from the first vertex */
    dfs_helper(graph->vertices, visited, 0, &max_depth, action);

    /* Free allocated memory */
    free(visited);

    return (max_depth);
}