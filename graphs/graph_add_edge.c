#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * connect_edge - Injects a single edge connection into a vertex adjacency list
 * @src_v: Source vertex pointer
 * @dest_v: Destination vertex pointer
 *
 * Return: 1 on success, 0 on memory failure
 */
int connect_edge(vertex_t *src_v, vertex_t *dest_v)
{
	edge_t *edge, *curr;

	edge = malloc(sizeof(edge_t));
	if (!edge)
		return (0);

	edge->dest = dest_v;
	edge->next = NULL;

	if (!src_v->edges)
	{
		src_v->edges = edge;
	}
	else
	{
		curr = src_v->edges;
		while (curr->next)
			curr = curr->next;
		curr->next = edge;
	}
	return (1);
}

/**
 * graph_add_edge - Establishes uni/bidirectional links between two vertices
 * @graph: Graph handle pointer
 * @src: String identifying source vertex
 * @dest: String identifying destination vertex
 * @type: Connection type (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on absolute success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   graph_edge_type_t type)
{
	vertex_t *v = NULL, *src_v = NULL, *dest_v = NULL;

	if (!graph || !src || !dest || (type != UNIDIRECTIONAL && type != BIDIRECTIONAL))
		return (0);

	/* Locate both the source and destination vertices in the graph list */
	for (v = graph->vertices; v; v = v->next)
	{
		if (strcmp(v->content, src) == 0)
			src_v = v;
		if (strcmp(v->content, dest) == 0)
			dest_v = v;
	}

	/* Error check: verify both vertices exist */
	if (!src_v || !dest_v)
		return (0);

	/* Establish the primary forward link */
	if (!connect_edge(src_v, dest_v))
		return (0);

	/* If bidirectional, establish the reverse link back to source */
	if (type == BIDIRECTIONAL && src_v != dest_v)
	{
		if (!connect_edge(dest_v, src_v))
			return (0);
	}

	return (1);
}


