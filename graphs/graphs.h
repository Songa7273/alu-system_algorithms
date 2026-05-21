#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * enum graph_edge_type_e - Defines the type of connection between vertices
 * @UNIDIRECTIONAL: One-way connection
 * @BIDIRECTIONAL: Two-way connection
 */
typedef enum graph_edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} graph_edge_type_t;

/* Forward declaration */
struct vertex_s;

/**
 * struct edge_s - Connection between two vertices
 * @dest: Pointer to the destination vertex
 * @next: Pointer to the next edge in the adjacency list
 */
typedef struct edge_s
{
	struct vertex_s *dest;
	struct edge_s *next;
} edge_t;

/**
 * struct vertex_s - Graph vertex node structure
 * @index: Unique index identifier of the vertex
 * @content: Allocated string data stored in the vertex
 * @edges: Pointer to the head of its edge adjacency linked list
 * @next: Pointer to the next vertex in the main graph chain
 */
typedef struct vertex_s
{
	size_t index;
	char *content;
	edge_t *edges;
	struct vertex_s *next;
} vertex_t;

/**
 * struct graph_s - Root graph manager structure
 * @nb_vertices: Current total number of vertices in the graph
 * @vertices: Pointer to the head of the vertex linked list
 */
typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t *vertices;
} graph_t;

/* Function Prototypes */
graph_t *graph_create(void);
vertex_t *graph_add_vertex(graph_t *graph, const char *str);
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   graph_edge_type_t type);
void graph_delete(graph_t *graph);

/* Helper display prototype given by project specifications */
void graph_display(const graph_t *graph);

#endif /* GRAPHS_H */
