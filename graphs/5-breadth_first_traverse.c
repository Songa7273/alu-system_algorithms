#include <stdlib.h>
#include "graphs.h"

/**
 * breadth_first_traverse - Traverses a graph using breadth-first search
 * @graph: Pointer to the graph to traverse
 * @action: Callback executed for each visited vertex
 *
 * Return: Biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
				     void (*action)(const vertex_t *v, size_t depth))
{
	const vertex_t **queue;
	size_t *depths;
	unsigned char *visited;
	size_t front = 0;
	size_t back = 0;
	size_t max_depth = 0;
	const vertex_t *vertex;
	edge_t *edge;

	if (!graph || !graph->vertices || !action)
		return (0);

	queue = malloc(sizeof(*queue) * graph->nb_vertices);
	depths = malloc(sizeof(*depths) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, sizeof(unsigned char));
	if (!queue || !depths || !visited)
	{
		free(queue);
		free(depths);
		free(visited);
		return (0);
	}

	queue[back] = graph->vertices;
	depths[back] = 0;
	visited[graph->vertices->index] = 1;
	back++;

	while (front < back)
	{
		vertex = queue[front];
		action(vertex, depths[front]);
		if (depths[front] > max_depth)
			max_depth = depths[front];

		for (edge = vertex->edges; edge; edge = edge->next)
		{
			if (!visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				queue[back] = edge->dest;
				depths[back] = depths[front] + 1;
				back++;
			}
		}
		front++;
	}

	free(queue);
	free(depths);
	free(visited);

	return (max_depth);
}
