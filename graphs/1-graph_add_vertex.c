#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 * @graph: Pointer to the graph to add the vertex to
 * @str: String to store in the new vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
    vertex_t *new_vertex, *current;
    char *str_copy;

    /* Check if graph and str are valid */
    if (!graph || !str)
        return (NULL);

    /* Check if a vertex with the same string already exists */
    current = graph->vertices;
    while (current)
    {
        if (strcmp(current->content, str) == 0)
            return (NULL);
        current = current->next;
    }

    /* Create a copy of the string */
    str_copy = strdup(str);
    if (!str_copy)
        return (NULL);

    /* Allocate memory for the new vertex */
    new_vertex = malloc(sizeof(vertex_t));
    if (!new_vertex)
    {
        free(str_copy);
        return (NULL);
    }

    /* Initialize the new vertex */
    new_vertex->index = graph->nb_vertices;
    new_vertex->content = str_copy;
    new_vertex->nb_edges = 0;
    new_vertex->edges = NULL;
    new_vertex->next = NULL;

    /* Add the new vertex to the graph */
    if (!graph->vertices)
    {
        /* First vertex in the graph */
        graph->vertices = new_vertex;
    }
    else
    {
        /* Add to the end of the list */
        current = graph->vertices;
        while (current->next)
            current = current->next;
        current->next = new_vertex;
    }

    /* Increment the number of vertices in the graph */
    graph->nb_vertices++;

    return (new_vertex);
}

