#include "graphs.h"
#include <stdlib.h>

/**
 * free_vertex_edges - Helper function to free all edges of a single vertex
 * @edge: Pointer to the head of the edge linked list
 */
void free_vertex_edges(edge_t *edge)
{
	edge_t *current_edge;
	edge_t *next_edge;

	current_edge = edge;
	while (current_edge != NULL)
	{
		next_edge = current_edge->next;
		free(current_edge);
		current_edge = next_edge;
	}
}

/**
 * graph_delete - Completely deletes an entire graph and all its components
 * @graph: Pointer to the graph structure to be deleted
 */
void graph_delete(graph_t *graph)
{
	vertex_t *current_vertex;
	vertex_t *next_vertex;

	if (graph == NULL)
		return;

	current_vertex = graph->vertices;
	while (current_vertex != NULL)
	{
		next_vertex = current_vertex->next;

		/* 1. Free the edge adjacency list for this vertex */
		if (current_vertex->edges != NULL)
		{
			free_vertex_edges(current_vertex->edges);
		}

		/* 2. Free the duplicated string content */
		if (current_vertex->content != NULL)
		{
			free(current_vertex->content);
		}

		/* 3. Free the vertex node structure itself */
		free(current_vertex);

		current_vertex = next_vertex;
	}

	/* 4. Free the root graph structure shell */
	free(graph);
}
