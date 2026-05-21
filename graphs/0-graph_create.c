#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create - creates a graph
 *
 * Return: pointer to the newly created graph,
 * or NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(graph_t));
	if (graph == NULL)
		return (NULL);

	graph->nodes = NULL;

	return (graph);
}
