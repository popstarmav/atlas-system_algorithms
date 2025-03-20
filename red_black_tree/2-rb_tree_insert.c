#include "rb_trees.h"
#include <stddef.h>

/**
 * rb_tree_uncle - Finds the uncle of a node
 * @node: Pointer to the node to find the uncle of
 *
 * Return: Pointer to the uncle node, or NULL if none
 */
rb_tree_t *rb_tree_uncle(rb_tree_t *node)
{
	if (node == NULL || node->parent == NULL || node->parent->parent == NULL)
		return (NULL);

	if (node->parent == node->parent->parent->left)
		return (node->parent->parent->right);
	return (node->parent->parent->left);
}

/**
 * rb_tree_rotate_left - Performs a left rotation on a Red-Black Tree
 * @tree: Double pointer to the root node of the tree
 * @node: Pointer to the node to rotate around
 */
void rb_tree_rotate_left(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *right = node->right;

	node->right = right->left;
	if (right->left != NULL)
		right->left->parent = node;

	right->parent = node->parent;
	if (node->parent == NULL)
		*tree = right;
	else if (node == node->parent->left)
		node->parent->left = right;
	else
		node->parent->right = right;

	right->left = node;
	node->parent = right;
}

/**
 * rb_tree_rotate_right - Performs a right rotation on a Red-Black Tree
 * @tree: Double pointer to the root node of the tree
 * @node: Pointer to the node to rotate around
 */
void rb_tree_rotate_right(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *left = node->left;

	node->left = left->right;
	if (left->right != NULL)
		left->right->parent = node;

	left->parent = node->parent;
	if (node->parent == NULL)
		*tree = left;
	else if (node == node->parent->right)
		node->parent->right = left;
	else
		node->parent->left = left;

	left->right = node;
	node->parent = left;
}

/**
 * fix_red_red_left - Fixes Red-Red violation when parent is a left child
 * @tree: Double pointer to the root node of the tree
 * @node: Pointer to the node with the violation
 * @uncle: Pointer to the uncle node
 *
 * Return: New position of the node after fixing
 */
rb_tree_t *fix_red_red_left(rb_tree_t **tree, rb_tree_t *node, rb_tree_t *uncle)
{
	if (uncle != NULL && uncle->color == RED)
	{
		node->parent->color = BLACK;
		uncle->color = BLACK;
		node->parent->parent->color = RED;
		return (node->parent->parent);
	}
	
	if (node == node->parent->right)
	{
		node = node->parent;
		rb_tree_rotate_left(tree, node);
	}
	
	node->parent->color = BLACK;
	node->parent->parent->color = RED;
	rb_tree_rotate_right(tree, node->parent->parent);
	
	return (node);
}

/**
 * fix_red_red_right - Fixes Red-Red violation when parent is a right child
 * @tree: Double pointer to the root node of the tree
 * @node: Pointer to the node with the violation
 * @uncle: Pointer to the uncle node
 *
 * Return: New position of the node after fixing
 */
rb_tree_t *fix_red_red_right(rb_tree_t **tree, rb_tree_t *node, rb_tree_t *uncle)
{
	if (uncle != NULL && uncle->color == RED)
	{
		node->parent->color = BLACK;
		uncle->color = BLACK;
		node->parent->parent->color = RED;
		return (node->parent->parent);
	}
	
	if (node == node->parent->left)
	{
		node = node->parent;
		rb_tree_rotate_right(tree, node);
	}
	
	node->parent->color = BLACK;
	node->parent->parent->color = RED;
	rb_tree_rotate_left(tree, node->parent->parent);
	
	return (node);
}

/**
 * rb_tree_fix_insert - Fixes the Red-Black Tree properties after insertion
 * @tree: Double pointer to the root node of the tree
 * @node: Pointer to the newly inserted node
 */
void rb_tree_fix_insert(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *uncle;

	while (node != *tree && node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;
			node = fix_red_red_left(tree, node, uncle);
		}
		else
		{
			uncle = node->parent->parent->left;
			node = fix_red_red_right(tree, node, uncle);
		}
		
		if (node == *tree)
			break;
	}
	
	(*tree)->color = BLACK;
}

/**
 * rb_tree_insert - Inserts a value in a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black tree
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node, *current, *parent = NULL;

	if (tree == NULL)
		return (NULL);

	/* Standard BST insertion */
	current = *tree;
	while (current != NULL)
	{
		parent = current;
		if (value < current->n)
			current = current->left;
		else if (value > current->n)
			current = current->right;
		else
			return (NULL); /* Value already exists */
	}

	new_node = rb_tree_node(parent, value, RED);
	if (new_node == NULL)
		return (NULL);

	if (parent == NULL)
		*tree = new_node;
	else if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	/* Handle root case and parent color cases */
	if (new_node->parent == NULL)
		new_node->color = BLACK;
	else if (new_node->parent->color == RED)
		rb_tree_fix_insert(tree, new_node);

	return (new_node);
}

