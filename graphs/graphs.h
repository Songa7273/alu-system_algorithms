#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * edge_s - graph edge
 */
typedef struct edge_s
{
    struct vertex_s *dest;
    struct edge_s *next;
} edge_t;

/**
 * vertex_s - graph vertex
 */
typedef struct vertex_s
{
    size_t index;
    char *content;
    edge_t *edges;
    struct vertex_s *next;
} vertex_t;

/**
 * graph_s - graph structure
 */
typedef struct graph_s
{
    size_t nb_vertices;
    vertex_t *vertices;
} graph_t;

/**
 * edge_type_t - edge type
 */
typedef enum edge_type_e
{
    UNIDIRECTIONAL,
    BIDIRECTIONAL
} edge_type_t;

/* ===== function prototypes ONLY (no code here) ===== */

graph_t *graph_create(void);

vertex_t *graph_add_vertex(graph_t *graph, const char *str);

int graph_add_edge(graph_t *graph,
                   const char *src,
                   const char *dest,
                   edge_type_t type);

void graph_display(const graph_t *graph);

#endif /* GRAPHS_H */
