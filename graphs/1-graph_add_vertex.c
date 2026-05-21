#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - adds a vertex to a graph
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new, *tmp, *last = NULL;

	if (graph == NULL || str == NULL)
		return (NULL);

	tmp = graph->vertices;

	/* check duplicates + find last node */
	while (tmp)
	{
		if (strcmp(tmp->content, str) == 0)
			return (NULL);
		last = tmp;
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
	new->next = NULL;

	/* assign index */
	if (last == NULL)
		new->index = 0;
	else
		new->index = last->index + 1;

	/* insert at end */
	if (last == NULL)
		graph->vertices = new;
	else
		last->next = new;

	graph->nb_vertices++;

	return (new);
}
