#include <stdlib.h>
#include "heap.h"

/**
 * swap_nodes - Swaps the data of two nodes
 *
 * @a: First node
 * @b: Second node
 */
void swap_nodes(binary_tree_node_t *a, binary_tree_node_t *b)
{
    void *temp;

    temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/**
 * heapify_up - Restores the min heap property by moving a node up
 *
 * @heap: Pointer to the heap
 * @node: Pointer to the node to heapify up
 *
 * Return: Pointer to the final position of the node
 */
binary_tree_node_t *heapify_up(heap_t *heap, binary_tree_node_t *node)
{
    if (!node || !node->parent)
        return (node);

    if (heap->data_cmp(node->data, node->parent->data) < 0)
    {
        swap_nodes(node, node->parent);
        return (heapify_up(heap, node->parent));
    }

    return (node);
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 *
 * @heap: Pointer to the heap
 * @data: Pointer to the data to store
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
    binary_tree_node_t *new_node = NULL, *current;
    size_t size, i;
    unsigned int bit;

    if (!heap || !data)
        return (NULL);

    /* If the heap is empty, create the root node */
    if (heap->root == NULL)
    {
        heap->root = binary_tree_node(NULL, data);
        if (heap->root == NULL)
            return (NULL);
        heap->size++;
        return (heap->root);
    }

    /* Find the position for the new node */
    size = heap->size + 1;
    current = heap->root;

    /* Find the highest bit in size */
    for (i = 0, bit = size; bit > 0; bit >>= 1, i++)
        ;
    i--; /* Adjust for the extra shift */

    /* Navigate to the parent of the new node using the bits of size */
    for (bit = 1 << (i - 1); bit > 1; bit >>= 1)
    {
        if (size & bit)
            current = current->right;
        else
            current = current->left;
    }

    /* Create the new node as left or right child */
    if (size & 1) /* Odd size means right child */
    {
        new_node = binary_tree_node(current, data);
        current->right = new_node;
    }
    else /* Even size means left child */
    {
        new_node = binary_tree_node(current, data);
        current->left = new_node;
    }

    if (!new_node)
        return (NULL);

    /* Increment heap size */
    heap->size++;

    /* Restore the min heap property */
    return (heapify_up(heap, new_node));
}
