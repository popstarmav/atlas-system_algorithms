#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * get_last_node - Gets the last node in the heap
 * @heap: Pointer to the heap
 * Return: Pointer to the last node
 */
binary_tree_node_t *get_last_node(heap_t *heap)
{
	binary_tree_node_t *node;
	size_t size, i, mask;

	if (!heap || !heap->root)
		return (NULL);

	node = heap->root;
	size = heap->size;

	mask = 1;
	for (i = 0; i < sizeof(size_t) * 8 - 1; i++)
	{
		if (mask << 1 > size)
			break;
		mask <<= 1;
	}

	mask >>= 1;
	while (mask > 0)
	{
		if (size & mask)
			node = node->right;
		else
			node = node->left;
		mask >>= 1;
	}

	return (node);
}

/**
 * find_parent - Finds the parent of a node
 * @root: Root of the tree
 * @node: Node to find parent of
 * Return: Pointer to parent node, or NULL if node is root
 */
binary_tree_node_t *find_parent(binary_tree_node_t *root,
		binary_tree_node_t *node)
{
	binary_tree_node_t *parent = NULL;

	if (!root || root == node)
		return (NULL);

	if (root->left == node || root->right == node)
		return (root);

	if (root->left)
	{
		parent = find_parent(root->left, node);
		if (parent)
			return (parent);
	}

	if (root->right)
	{
		parent = find_parent(root->right, node);
		if (parent)
			return (parent);
	}

	return (NULL);
}

/**
 * heapify_down - Restores the min heap property by moving a node down
 * @heap: Pointer to the heap
 * @node: Node to heapify down
 */
void heapify_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest = node;
	binary_tree_node_t *left = node->left;
	binary_tree_node_t *right = node->right;
	void *temp;

	if (left && heap->data_cmp(left->data, smallest->data) < 0)
		smallest = left;

	if (right && heap->data_cmp(right->data, smallest->data) < 0)
		smallest = right;

	if (smallest != node)
	{
		temp = node->data;
		node->data = smallest->data;
		smallest->data = temp;
		heapify_down(heap, smallest);
	}
}

/**
 * remove_last_node - Removes the last node from the heap
 * @heap: Pointer to the heap
 * @last: Pointer to the last node
 * Return: 1 on success, 0 on failure
 */
int remove_last_node(heap_t *heap, binary_tree_node_t *last)
{
	binary_tree_node_t *parent;

	parent = find_parent(heap->root, last);
	if (!parent && last != heap->root)
		return (0);

	if (parent)
	{
		if (parent->right == last)
			parent->right = NULL;
		else
			parent->left = NULL;
	}

	free(last);
	heap->size--;
	return (1);
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: Pointer to the heap
 * Return: Pointer to the data that was stored in the root node
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last_node;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last_node = get_last_node(heap);
	if (!last_node)
		return (NULL);

	heap->root->data = last_node->data;

	if (!remove_last_node(heap, last_node))
		return (NULL);

	if (heap->root)
		heapify_down(heap, heap->root);

	return (data);
}

