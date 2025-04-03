#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

/**
 * binary_tree_node - Creates a generic Binary Tree node
 * @parent: Pointer to the parent node
 * @data: Data to be stored in the node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new_node = malloc(sizeof(binary_tree_node_t));

	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
