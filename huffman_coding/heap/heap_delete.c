#include <stdlib.h>
#include "heap.h"

/**
 * free_tree - Recursively frees a binary tree
 * @node: Pointer to the current node
 * @free_data: Function to free the data in each node (can be NULL)
 */
void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node == NULL)
		return;

	/* Recursively free left and right subtrees */
	free_tree(node->left, free_data);
	free_tree(node->right, free_data);

	/* Free the data if free_data function is provided */
	if (free_data != NULL)
		free_data(node->data);

	/* Free the node itself */
	free(node);
}

/**
 * heap_delete - Deallocates a heap
 * @heap: Pointer to the heap to delete
 * @free_data: Function to free the data in each node (can be NULL)
 *
 * Description: Frees the entire tree starting at heap->root and the heap
 * structure itself. If free_data is NULL, the data stored in the nodes
 * must not be freed.
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
		return;

	/* Free the binary tree starting from the root */
	free_tree(heap->root, free_data);

	/* Free the heap structure itself */
	free(heap);
}
