#include "nary_trees.h"

/**
 * get_height - Gets height of an N-ary tree
 * @root: Root node pointer
 *
 * Return: Tree height
 */
size_t get_height(nary_tree_t const *root)
{
	size_t max_height = 0;
	nary_tree_t const *child;

	if (!root)
		return (0);

	child = root->children;
	while (child)
	{
		size_t height = get_height(child);

		if (height > max_height)
			max_height = height;
		child = child->next;
	}

	return (max_height + 1);
}

/**
 * find_diameter - Finds diameter recursively
 * @root: Root node pointer
 * @max_diameter: Current max diameter
 *
 * Return: Subtree height
 */
size_t find_diameter(nary_tree_t const *root, size_t *max_diameter)
{
	size_t highest = 0, second_highest = 0;
	nary_tree_t const *child;
	size_t path_through_root;
	size_t height;

	if (!root)
		return (0);

	/* Process each child */
	child = root->children;
	while (child)
	{
		height = find_diameter(child, max_diameter);

		if (height > highest)
		{
			second_highest = highest;
			highest = height;
		}
		else if (height > second_highest)
		{
			second_highest = height;
		}

		child = child->next;
	}

	/* Calculate path through this node */
	path_through_root = highest + second_highest + 1;

	/* Update max diameter if needed */
	if (root->children && path_through_root > *max_diameter)
		*max_diameter = path_through_root;

	return (highest + 1);
}

/**
 * nary_tree_diameter - Computes N-ary tree diameter
 * @root: Root node pointer
 *
 * Return: Tree diameter
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t max_diameter = 0;

	if (!root)
		return (0);

	find_diameter(root, &max_diameter);

	/* Handle single node case */
	if (max_diameter == 0 && root)
		return (1);

	return (max_diameter);
}

