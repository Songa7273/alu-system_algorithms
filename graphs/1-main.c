#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

int main(void)
{
	graph_t *graph;

	graph = graph_create();
	if (!graph)
		return (1);

	graph_add_vertex(graph, "San Francisco");
	graph_add_vertex(graph, "Seattle");

	printf("Vertices added successfully\n");
	return (0);
}
