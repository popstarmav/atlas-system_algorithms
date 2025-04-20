#include "nary_trees.h"

/**
 * nary_tree_traverse_recursive - Helper function for traversal
 * @node: Current node being traversed
 * @depth: Depth of the current node
 * @action: Function to execute for each node
 * @max_depth: Pointer to track maximum depth
 */
void nary_tree_traverse_recursive(nary_tree_t const *node, size_t depth,
		void (*action)(nary_tree_t const *node, size_t depth),
		size_t *max_depth)
{
	nary_tree_t const *child;

	if (!node)
		return;

	/* Execute action on current node */
	action(node, depth);

	/* Update max_depth if current depth is greater */
	if (depth > *max_depth)
		*max_depth = depth;

	/* Traverse all children */
	child = node->children;
	while (child)
	{
		nary_tree_traverse_recursive(child, depth + 1, action, max_depth);
		child = child->next;
	}
}

/**
 * nary_tree_traverse - Traverses an N-ary tree, node by node
 * @root: Pointer to the root node of the tree to traverse
 * @action: Function to execute for each node
 *
 * Return: The biggest depth of the tree
 */
size_t nary_tree_traverse(nary_tree_t const *root,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	size_t max_depth = 0;

	if (!root || !action)
		return (0);

	nary_tree_traverse_recursive(root, 0, action, &max_depth);

	return (max_depth);
}

