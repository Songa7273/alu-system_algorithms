#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

int main(void)
{
	graph_t *graph;

	graph = graph_create();

	graph_add_vertex(graph, "A");
	graph_add_vertex(graph, "B");

	graph_add_edge(graph, "A", "B", BIDIRECTIONAL);

	graph_display(graph);

	return (0);
}
