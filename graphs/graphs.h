#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * vertex structure
 */
typedef struct vertex_s
{
    char *name;
    struct edge_s *edges;
    struct vertex_s *next;
} vertex_t;

/**
 * edge structure
 */
typedef struct edge_s
{
    vertex_t *dest;
    struct edge_s *next;
} edge_t;

/**
 * graph structure
 */
typedef struct graph_s
{
    size_t nb_vertices;
    vertex_t *vertices;
} graph_t;

graph_t *graph_create(void);

#endif
