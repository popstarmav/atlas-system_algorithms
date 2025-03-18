#include "rb_trees.h"
#include <stddef.h>
#include <limits.h>
/**
 * is_bst - Checks if a tree is a valid Binary Search Tree
 * @tree: Pointer to the root node of the tree
 * @min: Minimum value nodes can have
 * @max: Maximum value nodes can have
 *
 * Return: 1 if valid BST, 0 otherwise
 */
int is_bst(const rb_tree_t *tree, int min, int max)
{
    if (tree == NULL)
        return 1;

    if (tree->n <= min || tree->n >= max)
        return 0;

    return is_bst(tree->left, min, tree->n) &&
           is_bst(tree->right, tree->n, max);
}

/**
 * check_red_property - Checks if there are no two adjacent red nodes
 * @tree: Pointer to the root node of the tree
 *
 * Return: 1 if property is respected, 0 otherwise
 */
int check_red_property(const rb_tree_t *tree)
{
    if (tree == NULL)
        return 1;

    if (tree->color == RED)
    {
        if ((tree->left && tree->left->color == RED) ||
            (tree->right && tree->right->color == RED))
            return 0;
    }

    return check_red_property(tree->left) && check_red_property(tree->right);
}

/**
 * count_black_nodes - Counts black nodes from root to leaf
 * @tree: Pointer to the root node of the tree
 *
 * Return: Number of black nodes, or -1 if paths have different counts
 */
int count_black_nodes(const rb_tree_t *tree)
{
    int left_count, right_count;

    if (tree == NULL)
        return 0;

    left_count = count_black_nodes(tree->left);
    right_count = count_black_nodes(tree->right);

    if (left_count == -1 || right_count == -1 || left_count != right_count)
        return -1;

    return left_count + (tree->color == BLACK ? 1 : 0);
}

/**
 * rb_tree_is_valid - Checks if a binary tree is a valid Red-Black Tree
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
    if (tree == NULL)
        return 0;

    /* Property 1: Root is black */
    if (tree->color != BLACK)
        return 0;

    /* Property 2: Tree is a BST */
    if (!is_bst(tree, INT_MIN, INT_MAX))
        return 0;

    /* Property 3: No two adjacent red nodes */
    if (!check_red_property(tree))
        return 0;

    /* Property 4: Every path from root to leaf has same number of black nodes */
    if (count_black_nodes(tree) == -1)
        return 0;

    return 1;
}

