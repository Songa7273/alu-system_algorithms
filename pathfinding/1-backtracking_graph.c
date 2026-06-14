#include "pathfinding.h"

/**
 * backtrack_graph_rec - Recursive helper function using backtracking on graph.
 * @curr: Current structural vertex pointer.
 * @target: Target destination vertex pointer.
 * @visited: Tracking array for visited indices.
 * @path: The collection queue holding path structures.
 *
 * Return: 1 if target path is resolved, 0 otherwise.
 */
int backtrack_graph_rec(vertex_t const *curr, vertex_t const *target,
			char *visited, queue_t *path)
{
	edge_t *edge;
	char *city_copy;

	if (!curr || visited[curr->index])
		return (0);

	printf("Checking %s\n", curr->content);
	visited[curr->index] = 1;

	if (curr == target)
	{
		city_copy = strdup(curr->content);
		if (!city_copy)
			return (0);
		queue_push_front(path, city_copy);
		return (1);
	}

	for (edge = curr->edges; edge; edge = edge->next)
	{
		if (backtrack_graph_rec(edge->dest, target, visited, path))
		{
			city_copy = strdup(curr->content);
			if (!city_copy)
				return (0);
			queue_push_front(path, city_copy);
			return (1);
		}
	}

	return (0);
}

/**
 * backtracking_graph - Searches for the first path from a starting point
 * to a target point in a graph using backtracking.
 * @graph: Pointer to the graph to traverse.
 * @start: Pointer to the starting vertex.
 * @target: Pointer to the target vertex.
 *
 * Return: Allocated queue pathway if valid, NULL on failure.
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	queue_t *path;
	char *visited;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}

	if (!backtrack_graph_rec(start, target, visited, path))
	{
		free(visited);
		queue_delete(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
