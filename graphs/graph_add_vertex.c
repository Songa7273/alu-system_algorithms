#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * graph_add_vertex - Adds a vertex to a graph
 * @graph: Pointer to the graph
 * @str: String content of the vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex;

	if (!graph || !str)
		return (NULL);

	vertex = malloc(sizeof(vertex_t));
	if (!vertex)
		return (NULL);

	vertex->content = strdup(str);
	if (!vertex->content)
	{
		free(vertex);
		return (NULL);
	}

	vertex->index = graph->nb_vertices;
	vertex->edges = NULL;

	vertex->next = graph->vertices;
	graph->vertices = vertex;

	graph->nb_vertices++;

	return (vertex);
}
