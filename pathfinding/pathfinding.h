#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>

/**
 * struct point_s - point in grid
 * @x: x coordinate
 * @y: y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
 * struct queue_node_s - queue node
 * @data: stored data
 * @next: next node
 */
typedef struct queue_node_s
{
	void *data;
	struct queue_node_s *next;
} queue_node_t;

/**
 * struct queue_s - queue structure
 * @front: front node
 * @rear: rear node
 */
typedef struct queue_s
{
	queue_node_t *front;
	queue_node_t *rear;
} queue_t;

/* Queue functions */
queue_t *create_queue(void);
void enqueue(queue_t *queue, void *data);
void *dequeue(queue_t *queue);
void free_queue(queue_t *queue);

/* Pathfinding */
queue_t *backtracking_array(char **grid, int rows, int cols,
				point_t start, point_t goal);

#endif
