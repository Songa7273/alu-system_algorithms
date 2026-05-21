#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * find_vertex - finds a vertex by name
 */
static vertex_t *find_vertex(graph_t *graph, const char *str)
{
	vertex_t *tmp;

	tmp = graph->vertices;

	while (tmp)
	{
		if (strcmp(tmp->content, str) == 0)
			return (tmp);
		tmp = tmp->next;
	}

	return (NULL);
}

/**
 * add_edge_node - adds edge to adjacency list
 */
static edge_t *add_edge_node(vertex_t *src, vertex_t *dest)
{
	edge_t *edge, *tmp;

	edge = malloc(sizeof(edge_t));
	if (edge == NULL)
		return (NULL);

	edge->dest = dest;
	edge->next = NULL;

	if (src->edges == NULL)
	{
		src->edges = edge;
		return (edge);
	}

	tmp = src->edges;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = edge;

	return (edge);
}

/**
 * graph_add_edge - adds edge(s) between vertices
 */
int graph_add_edge(graph_t *graph, const char *src,
					const char *dest, edge_type_t type)
{
	vertex_t *v_src, *v_dest;

	if (graph == NULL || src == NULL || dest == NULL)
		return (0);

	v_src = find_vertex(graph, src);
	v_dest = find_vertex(graph, dest);

	if (v_src == NULL || v_dest == NULL)
		return (0);

	if (add_edge_node(v_src, v_dest) == NULL)
		return (0);

	if (type == BIDIRECTIONAL)
	{
		if (add_edge_node(v_dest, v_src) == NULL)
			return (0);
	}

	return (1);
}
