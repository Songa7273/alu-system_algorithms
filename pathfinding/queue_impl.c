#include <stdlib.h>
#include "pathfinding.h"

queue_t *queue_create(void)
{
	queue_t *q = malloc(sizeof(queue_t));

	if (!q)
		return NULL;

	q->front = NULL;
	q->rear = NULL;
	return q;
}

void enqueue(queue_t *q, void *data)
{
	queue_node_t *node = malloc(sizeof(queue_node_t));

	if (!q || !node)
		return;

	node->data = data;
	node->next = NULL;

	if (!q->rear)
	{
		q->front = q->rear = node;
		return;
	}

	q->rear->next = node;
	q->rear = node;
}

void *dequeue(queue_t *q)
{
	queue_node_t *tmp;
	void *data;

	if (!q || !q->front)
		return NULL;

	tmp = q->front;
	data = tmp->data;
	q->front = q->front->next;

	if (!q->front)
		q->rear = NULL;

	free(tmp);
	return data;
}

void queue_push_front(queue_t *q, void *data)
{
	queue_node_t *node = malloc(sizeof(queue_node_t));

	if (!q || !node)
		return;

	node->data = data;
	node->next = q->front;
	q->front = node;

	if (!q->rear)
		q->rear = node;
}
