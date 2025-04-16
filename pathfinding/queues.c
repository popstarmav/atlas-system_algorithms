#include "queues.h"
#include <stdlib.h>

/**
 * queue_create - Creates a queue
 *
 * Return: Pointer to the newly created queue
 */
queue_t *queue_create(void)
{
    queue_t *queue;

    queue = malloc(sizeof(queue_t));
    if (!queue)
        return (NULL);

    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;

    return (queue);
}

/**
 * queue_delete - Deletes a queue
 *
 * @queue: Pointer to the queue to delete
 */
void queue_delete(queue_t *queue)
{
    queue_node_t *node, *next;

    if (!queue)
        return;

    node = queue->front;
    while (node)
    {
        next = node->next;
        free(node);
        node = next;
    }

    free(queue);
}

/**
 * queue_push_back - Pushes an element at the back of a queue
 *
 * @queue: Pointer to the queue
 * @ptr: Data to store in the new node
 * Return: Pointer to the newly created node, NULL on failure
 */
void *queue_push_back(queue_t *queue, void *ptr)
{
    queue_node_t *node;

    if (!queue)
        return (NULL);

    node = malloc(sizeof(queue_node_t));
    if (!node)
        return (NULL);

    node->ptr = ptr;
    node->next = NULL;
    node->prev = queue->back;

    if (!queue->front)
        queue->front = node;
    else
        queue->back->next = node;

    queue->back = node;
    queue->size++;

    return (node);
}

/**
 * queue_push_front - Pushes an element at the front of a queue
 *
 * @queue: Pointer to the queue
 * @ptr: Data to store in the new node
 * Return: Pointer to the newly created node, NULL on failure
 */
void *queue_push_front(queue_t *queue, void *ptr)
{
    queue_node_t *node;

    if (!queue)
        return (NULL);

    node = malloc(sizeof(queue_node_t));
    if (!node)
        return (NULL);

    node->ptr = ptr;
    node->prev = NULL;
    node->next = queue->front;

    if (!queue->back)
        queue->back = node;
    else
        queue->front->prev = node;

    queue->front = node;
    queue->size++;

    return (node);
}

/**
 * dequeue - Pops an element from a queue
 *
 * @queue: Pointer to the queue
 * Return: Data stored in the popped element
 */
void *dequeue(queue_t *queue)
{
    queue_node_t *node;
    void *ptr;

    if (!queue || !queue->front)
        return (NULL);

    node = queue->front;
    ptr = node->ptr;

    queue->front = node->next;
    if (queue->front)
        queue->front->prev = NULL;
    else
        queue->back = NULL;

    free(node);
    queue->size--;

    return (ptr);
}

