#include "pathfinding.h"

/**
 * create_queue - creates empty queue
 */
queue_t *create_queue(void)
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;

    q->front = NULL;
    q->rear = NULL;
    return q;
}

/**
 * enqueue - adds element to queue
 */
void enqueue(queue_t *q, void *data)
{
    queue_node_t *node = malloc(sizeof(queue_node_t));

    if (!q || !node)
        return;

    node->data = data;
    node->next = NULL;

    if (q->rear)
        q->rear->next = node;
    else
        q->front = node;

    q->rear = node;
}

/**
 * dequeue - removes element
 */
void *dequeue(queue_t *q)
{
    queue_node_t *tmp;
    void *data;

    if (!q || !q->front)
        return NULL;

    tmp = q->front;
    data = tmp->data;
    q->front = tmp->next;

    if (!q->front)
        q->rear = NULL;

    free(tmp);
    return data;
}

/**
 * is_empty - checks queue
 */
int is_empty(queue_t *q)
{
    return (!q || !q->front);
}

/**
 * free_queue - frees queue nodes only
 */
void free_queue(queue_t *q)
{
    if (!q)
        return;

    while (!is_empty(q))
        free(dequeue(q));

    free(q);
}
