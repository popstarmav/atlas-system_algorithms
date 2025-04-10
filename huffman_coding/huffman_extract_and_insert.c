#include "huffman.h"
#include "heap/heap.h"
#include <stdlib.h>

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts a new one
 * @priority_queue: Pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_node;
	binary_tree_node_t *nested1, *nested2, *new_nested;
	symbol_t *symbol1, *symbol2, *new_symbol;

	if (!priority_queue || !priority_queue->root || priority_queue->size < 2)
		return (0);

	/* Extract the two nodes with the lowest frequencies */
	node1 = heap_extract(priority_queue);
	if (!node1)
		return (0);

	node2 = heap_extract(priority_queue);
	if (!node2)
	{
		heap_insert(priority_queue, node1);
		return (0);
	}

	/* Get the nested nodes and symbols */
	nested1 = (binary_tree_node_t *)(node1->data);
	nested2 = (binary_tree_node_t *)(node2->data);
	symbol1 = (symbol_t *)(nested1->data);
	symbol2 = (symbol_t *)(nested2->data);

	/* Create a new symbol with the sum of frequencies */
	new_symbol = symbol_create(-1, symbol1->freq + symbol2->freq);
	if (!new_symbol)
	{
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	/* Create a new nested node with the new symbol */
	new_nested = binary_tree_node(NULL, new_symbol);
	if (!new_nested)
	{
		free(new_symbol);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	/* Set the extracted nested nodes as children of the new nested node */
	new_nested->left = nested1;
	new_nested->right = nested2;

	/* Create a new node for the priority queue */
	new_node = binary_tree_node(NULL, new_nested);
	if (!new_node)
	{
		free(new_symbol);
		free(new_nested);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	/* Insert the new node into the priority queue */
	if (!heap_insert(priority_queue, new_node))
	{
		free(new_symbol);
		free(new_nested);
		free(new_node);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	/* Free the old nodes from the priority queue */
	free(node1);
	free(node2);

	return (1);
}

