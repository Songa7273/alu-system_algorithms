#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>

/* ===================== */
/* Structures */
/* ===================== */

typedef struct point_s
{
	int x;
	int y;
} point_t;

/* Queue node (from libqueues) */
typedef struct queue_node_s
{
	void *data;
	struct queue_node_s *next;
} queue_node_t;

/* Queue structure */
typedef struct queue_s
{
	queue_node_t *front;
	queue_node_t *rear;
} queue_t;

/* ===================== */
/* Queue functions (from libqueues) */
/* ===================== */

queue_t *queue_create(void);
void enqueue(queue_t *queue, void *data);
void *dequeue(queue_t *queue);
void queue_push_front(queue_t *queue, void *data);

/* ===================== */
/* Your function */
/* ===================== */

queue_t *backtracking_array(char **map, int rows, int cols,
							 point_t const *start,
							 point_t const *target);

#endif /* PATHFINDING_H */
