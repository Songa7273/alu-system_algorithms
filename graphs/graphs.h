#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * struct edge_s - represents an edge in the graph
 */
typedef struct edge_s
{
    struct vertex_s *dest;
    struct edge_s *next;
} edge_t;

/**
 * struct vertex_s - represents a vertex in the graph
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

/* function prototypes */
graph_t *graph_create(void);

#endif /* GRAPHS_H */
