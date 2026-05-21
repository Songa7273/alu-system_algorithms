#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - adds a vertex to a graph
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new, *tmp;

	if (graph == NULL || str == NULL)
		return (NULL);

	/* check duplicates */
	tmp = graph->vertices;
	while (tmp)
	{
		if (strcmp(tmp->content, str) == 0)
			return (NULL);
		tmp = tmp->next;
	}

	new = malloc(sizeof(vertex_t));
	if (new == NULL)
		return (NULL);

	new->content = strdup(str);
	if (new->content == NULL)
	{
		free(new);
		return (NULL);
	}

	new->edges = NULL;
	new->next = graph->vertices;

	graph->vertices = new;
	graph->nb_vertices++;

	return (new);
}
