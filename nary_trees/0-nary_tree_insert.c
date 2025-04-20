#include <stdlib.h>
#include <string.h>
#include "nary_trees.h"

/**
 * nary_tree_insert - Inserts a node in an N-ary tree
 * @parent: Pointer to the parent node
 * @str: String to be stored in the created node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node;

	/* Create new node */
	new_node = malloc(sizeof(nary_tree_t));
	if (!new_node)
		return (NULL);

	/* Copy string */
	new_node->content = strdup(str);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}

	/* Init node */
	new_node->parent = parent;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;

	/* Add to parent's children list */
	if (parent)
	{
		new_node->next = parent->children;
		parent->children = new_node;
		parent->nb_children++;
	}

	return (new_node);
}

