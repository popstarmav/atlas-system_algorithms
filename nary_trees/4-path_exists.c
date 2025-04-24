#include "nary_trees.h"
#include <string.h>

/**
 * path_exists - Checks if a path exists in an N-ary tree
 * @root: Pointer to the root node of the tree
 * @path: NULL terminated array of strings representing the path
 *
 * Return: 1 if path exists, 0 otherwise
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t const *current;
	int i = 0;

	if (!root || !path || !path[0])
		return (0);

	/* Check if root matches first element in path */
	if (strcmp(root->content, path[0]) != 0)
		return (0);

	/* Start from root and follow the path */
	current = root;
	i = 1;

	/* While we have more path elements to check */
	while (path[i] != NULL)
	{
		int found = 0;
		nary_tree_t const *child = current->children;

		/* Look for the current path element among the children */
		while (child)
		{
			if (strcmp(child->content, path[i]) == 0)
			{
				found = 1;
				current = child;
				break;
			}
			child = child->next;
		}

		/* If we didn't find the path element, path doesn't exist */
		if (!found)
			return (0);

		i++;
	}

	/* If we've checked all path elements, the path exists */
	return (1);
}

