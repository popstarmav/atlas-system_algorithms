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

    if (!graph || !str)
        return (NULL);

    /* Check if vertex already exists */
    current = graph->vertices;
    while (current)
    {
        if (strcmp(current->content, str) == 0)
            return (NULL);
        current = current->next;
    }

    /* Create new vertex */
    str_copy = strdup(str);
    if (!str_copy)
        return (NULL);

    new_vertex = malloc(sizeof(vertex_t));
    if (!new_vertex)
    {
        free(str_copy);
        return (NULL);
    }

    /* Initialize vertex */
    new_vertex->index = graph->nb_vertices;
    new_vertex->content = str_copy;
    new_vertex->nb_edges = 0;
    new_vertex->edges = NULL;
    new_vertex->next = NULL;

    /* Add vertex to graph */
    if (!graph->vertices)
        graph->vertices = new_vertex;
    else
    {
        current = graph->vertices;
        while (current->next)
            current = current->next;
        current->next = new_vertex;
    }

    graph->nb_vertices++;
    return (new_vertex);
}

