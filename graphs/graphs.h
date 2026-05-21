#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * struct edge_s - graph edge
 */
typedef struct edge_s
{
	struct vertex_s *dest;
	struct edge_s *next;
} edge_t;

/**
 * struct vertex_s - graph vertex
 */
typedef struct vertex_s
{
	char *content;
	edge_t *edges;
	struct vertex_s *next;
} vertex_t;

/**
 * struct graph_s - graph structure
 */
typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t *vertices;
} graph_t;

/* functions */
graph_t *graph_create(void);
vertex_t *graph_add_vertex(graph_t *graph, const char *str);

#endif
