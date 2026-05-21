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
	vertex_t *current;
	vertex_t *tail;

	if (!graph || !str)
		return (NULL);

	for (current = graph->vertices; current; current = current->next)
	{
		if (strcmp(current->content, str) == 0)
			return (NULL);
	}

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
	vertex->next = NULL;

	if (!graph->vertices)
	{
		graph->vertices = vertex;
	}
	else
	{
		tail = graph->vertices;
		while (tail->next)
			tail = tail->next;
		tail->next = vertex;
	}

	graph->nb_vertices++;

	return (vertex);
}


