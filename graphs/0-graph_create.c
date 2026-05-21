#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create - Creates a graph
 *
 * Return: Pointer to the created graph, or NULL on failure
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
