#include <stdlib.h>
#include "heap.h"

/**
 * get_parent_node - Gets the parent node at a specific index
 *
 * @root: Pointer to the root of the tree
 * @index: Index of the node to find
 * @current_index: Current index in the traversal
 *
 * Return: Pointer to the parent node
 */
binary_tree_node_t *get_parent_node(binary_tree_node_t *root, size_t index,
                                   size_t current_index)
{
    binary_tree_node_t *left, *right;

    if (current_index == (index / 2))
        return (root);

    if (index < (2 * current_index + 1))
        return (NULL);

    left = get_parent_node(root->left, index, 2 * current_index + 1);
    if (left)
        return (left);

    right = get_parent_node(root->right, index, 2 * current_index + 2);
    return (right);
}

/**
 * heapify_up - Restores the min heap property by moving a node up
 *
 * @heap: Pointer to the heap
 * @node: Pointer to the node to heapify up
 *
 * Return: Pointer to the final position of the node
 */
binary_tree_node_t *heapify_up(heap_t *heap, binary_tree_node_t *node)
{
    void *temp;

    if (!node || !node->parent)
        return (node);

    if (heap->data_cmp(node->data, node->parent->data) < 0)
    {
        /* Swap data with parent */
        temp = node->data;
        node->data = node->parent->data;
        node->parent->data = temp;

        /* Continue heapifying up */
        return (heapify_up(heap, node->parent));
    }

    return (node);
}

/**
 * insert_at_position - Inserts a node at a specific position in the heap
 *
 * @heap: Pointer to the heap
 * @data: Data to insert
 * @index: Position to insert at
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
binary_tree_node_t *insert_at_position(heap_t *heap, void *data, size_t index)
{
    binary_tree_node_t *parent, *new_node;

    if (index == 0)
    {
        heap->root = binary_tree_node(NULL, data);
        return (heap->root);
    }

    parent = get_parent_node(heap->root, index, 0);
    if (!parent)
        return (NULL);

    if (index % 2) /* Odd index means left child */
        parent->left = binary_tree_node(parent, data);
    else /* Even index means right child */
        parent->right = binary_tree_node(parent, data);

    new_node = (index % 2) ? parent->left : parent->right;
    if (!new_node)
        return (NULL);

    return (heapify_up(heap, new_node));
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 *
 * @heap: Pointer to the heap
 * @data: Pointer to the data to store
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
    binary_tree_node_t *node;

    if (!heap || !data)
        return (NULL);

    node = insert_at_position(heap, data, heap->size);
    if (node)
        heap->size++;

    return (node);
}
