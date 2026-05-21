#include <stdlib.h>
#include "graphs.h"

/**
 * dfs_visit - Recursive helper for depth-first traversal
 * @vertex: Current vertex
 * @depth: Depth of the current vertex
 * @action: Callback executed on each visited vertex
 * @visited: Array tracking already visited vertex indices
 * @max_depth: Pointer to the maximum depth found so far
 */
static void dfs_visit(const vertex_t *vertex, size_t depth,
			 void (*action)(const vertex_t *v, size_t depth),
			 unsigned char *visited, size_t *max_depth)
{
	edge_t *edge;

	visited[vertex->index] = 1;
	action(vertex, depth);
	if (depth > *max_depth)
		*max_depth = depth;

	for (edge = vertex->edges; edge; edge = edge->next)
	{
		if (!visited[edge->dest->index])
			dfs_visit(edge->dest, depth + 1, action, visited, max_depth);
	}
}

/**
 * depth_first_traverse - Traverses a graph using depth-first search
 * @graph: Pointer to the graph to traverse
 * @action: Callback executed for each visited vertex
 *
 * Return: Biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	unsigned char *visited;
	size_t max_depth = 0;

	if (!graph || !graph->vertices || !action)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(unsigned char));
	if (!visited)
		return (0);

	dfs_visit(graph->vertices, 0, action, visited, &max_depth);
	free(visited);

	return (max_depth);
}
