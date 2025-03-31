#include "heap.h"
#include <stdlib.h>

/**
 * heap_create - Creates a heap data structure
 * @data_cmp: Pointer to a comparison function
 *
 * Return: Pointer to the created heap, or NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
    heap_t *heap;

    /* Check if comparison function is provided */
    if (data_cmp == NULL)
        return (NULL);

    /* Allocate memory for the heap structure */
    heap = malloc(sizeof(heap_t));
    if (heap == NULL)
        return (NULL);

    /* Initialize heap properties */
    heap->size = 0;
    heap->data_cmp = data_cmp;
    heap->root = NULL;

    return (heap);
}
