#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

/* Directions for task 0 */
#define RIGHT 0
#define BOTTOM 1
#define LEFT 2
#define TOP 3

/* Queue and Graph types from the static libraries */
typedef struct qnode_s
{
	void *ptr;
	struct qnode_s *next;
	struct qnode_s *prev;
} qnode_t;

typedef struct queue_s
{
	qnode_t *front;
	qnode_t *rear;
} queue_t;

typedef enum edge_type_e
{
	UNIDIRECTIONAL,
	BIDIRECTIONAL
} edge_type_t;

typedef struct edge_s
{
	struct vertex_s *dest;
	int weight;
	struct edge_s *next;
} edge_t;

typedef struct vertex_s
{
	size_t index;
	char *content;
	int x;
	int y;
	edge_t *edges;
	struct vertex_s *next;
} vertex_t;

typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t *vertices;
} graph_t;

/* Library helper prototypes */
queue_t *queue_create(void);
qnode_t *queue_push_back(queue_t *queue, void *ptr);
void *dequeue(queue_t *queue);
void queue_delete(queue_t *queue);
/* Compatibility macro for varying main.c implementations */
#define free_queue queue_delete

graph_t *graph_create(void);
vertex_t *graph_add_vertex(graph_t *graph, const char *content, int x, int y);
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   int weight, edge_type_t type);
void graph_delete(graph_t *graph);

/* Mandatory project task prototypes */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);

queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target);

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target);

#endif /* PATHFINDING_H */
