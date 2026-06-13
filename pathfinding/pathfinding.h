#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>

typedef struct point_s
{
	int x;
	int y;
} point_t;

typedef struct queue_node_s
{
	void *data;
	struct queue_node_s *next;
} queue_node_t;

typedef struct queue_s
{
	queue_node_t *front;
	queue_node_t *rear;
} queue_t;

queue_t *create_queue(void);
void enqueue(queue_t *queue, void *data);
void *dequeue(queue_t *queue);
void free_queue(queue_t *queue);

queue_t *backtracking_array(char **grid, int rows, int cols,
				point_t start, point_t goal);

#endif
