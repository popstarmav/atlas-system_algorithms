#include <stdlib.h>
#include "nary_trees.h"

/**
 * nary_tree_delete - Deallocates an entire N-ary tree
 * @tree: Pointer to the root node of the tree to delete
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *current, *next;

	if (!tree)
		return;

	/* First delete all children */
	current = tree->children;
	while (current)
	{
		next = current->next;
		nary_tree_delete(current);
		current = next;
	}

	/* Then free the content and the node itself */
	free(tree->content);
	free(tree);
}

