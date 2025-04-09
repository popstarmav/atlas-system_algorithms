#include "huffman.h"
#include "heap/heap.h"
#include <stdlib.h>

/**
 * symbol_cmp - Compares two symbols based on their frequencies
 * @p1: First symbol (binary_tree_node_t containing symbol_t)
 * @p2: Second symbol (binary_tree_node_t containing symbol_t)
 *
 * Return: Difference between frequencies
 */
int symbol_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1, *node2;
	symbol_t *symbol1, *symbol2;

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;
	symbol1 = (symbol_t *)(node1->data);
	symbol2 = (symbol_t *)(node2->data);

	return (symbol1->freq - symbol2->freq);
}

/**
 * create_and_insert_node - Creates and inserts a node into the priority queue
 * @priority_queue: The priority queue
 * @data: The character
 * @freq: The frequency
 *
 * Return: 1 on success, 0 on failure
 */
int create_and_insert_node(heap_t *priority_queue, char data, size_t freq)
{
	binary_tree_node_t *nested_node;
	symbol_t *symbol;

	/* Create a symbol with the character and its frequency */
	symbol = symbol_create(data, freq);
	if (!symbol)
		return (0);

	/* Create a binary tree node with the symbol as data */
	nested_node = binary_tree_node(NULL, symbol);
	if (!nested_node)
	{
		free(symbol);
		return (0);
	}

	/* Insert the binary tree node into the min heap */
	if (heap_insert(priority_queue, nested_node) == NULL)
	{
		free(symbol);
		free(nested_node);
		return (0);
	}

	return (1);
}

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the created min heap (priority queue)
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	size_t i;

	/* Create the min heap */
	priority_queue = heap_create(symbol_cmp);
	if (!priority_queue)
		return (NULL);

	/* For each character, create a symbol and add it to the min heap */
	for (i = 0; i < size; i++)
	{
		if (!create_and_insert_node(priority_queue, data[i], freq[i]))
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	return (priority_queue);
}

