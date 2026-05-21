#include <stdio.h>
#include "graphs.h"

/**
 * graph_display - prints all vertices in the graph
 */
void graph_display(const graph_t *graph)
{
	vertex_t *v;

	if (graph == NULL)
		return;

	printf("Number of vertices: %lu\n", graph->nb_vertices);

	v = graph->vertices;
	while (v)
	{
		printf("[%lu] %s\n", v->index, v->content);
		v = v->next;
	}
}
