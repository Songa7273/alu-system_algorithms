#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * struct graph_node_s - graph node structure
 *
 * @content: string stored in the node
 * @index: index of the node
 * @nb_edges: number of edges
 * @edges: array of pointers to connected nodes
 * @next: pointer to the next node
 */
typedef struct graph_node_s
{
	char *content;
	size_t index;
	size_t nb_edges;
	struct graph_node_s **edges;
	struct graph_node_s *next;
} graph_node_t;

/**
 * struct graph_s - graph structure
 *
 * @nodes: linked list of graph nodes
 */
typedef struct graph_s
{
	graph_node_t *nodes;
} graph_t;

graph_t *graph_create(void);

#endif /* GRAPHS_H */
