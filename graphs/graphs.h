#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * struct graph_node_s - Graph node structure
 * @content: String stored in the node
 * @index: Index of the node
 * @nb_edges: Number of edges
 * @edges: Array of pointers to connected nodes
 * @next: Pointer to the next node
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
 * struct graph_s - Graph structure
 * @nodes: Linked list of graph nodes
 */
typedef struct graph_s
{
	graph_node_t *nodes;
} graph_t;

graph_t *graph_create(void);

#endif /* GRAPHS_H */
