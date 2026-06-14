#include "pathfinding.h"
#include <limits.h>

/**
 * find_min_vertex - Finds the unvisited vertex with the minimum distance.
 * @graph: Pointer to the graph.
 * @dist: Array of distances from the start vertex.
 * @visited: Array tracking visited vertices.
 *
 * Return: Pointer to the vertex with the minimum distance, or NULL.
 */
static vertex_t *find_min_vertex(graph_t *graph, int *dist, char *visited)
{
	vertex_t *min_v = NULL;
	vertex_t *v;
	int min_dist = INT_MAX;

	for (v = graph->vertices; v; v = v->next)
	{
		if (!visited[v->index] && dist[v->index] < min_dist)
		{
			min_dist = dist[v->index];
			min_v = v;
		}
	}
	return (min_v);
}

/**
 * build_dijkstra_path - Unwinds parent tracks to populate the path queue.
 * @target: Target destination vertex.
 * @parent: Array tracking parent vertices for shortest path tracing.
 * @path: Allocated queue pointer.
 *
 * Return: 1 on success, 0 on memory allocation failure.
 */
static int build_dijkstra_path(vertex_t const *target, vertex_t **parent,
			       queue_t *path)
{
	vertex_t const *curr = target;
	char *city;

	while (curr)
	{
		city = strdup(curr->content);
		if (!city)
			return (0);
		if (!queue_push_front(path, city))
		{
			free(city);
			return (0);
		}
		curr = parent[curr->index];
	}
	return (1);
}

/**
 * init_dijkstra - Initializes tracking data spaces.
 * @graph: Graph pointer.
 * @start: Starting vertex pointer.
 * @dist: Distance tracker array.
 *
 * Return: void.
 */
static void init_dijkstra(graph_t *graph, vertex_t const *start, int *dist)
{
	vertex_t *u;

	for (u = graph->vertices; u; u = u->next)
		dist[u->index] = INT_MAX;
	dist[start->index] = 0;
}

/**
 * dijkstra_graph - Finds the shortest path in a graph using Dijkstra's.
 * @graph: Pointer to the graph to process.
 * @start: Pointer to the starting vertex.
 * @target: Pointer to the target vertex.
 *
 * Return: Allocated queue pathway on success, NULL on failure.
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	queue_t *path = NULL;
	int *dist = NULL;
	char *visited = NULL;
	vertex_t **parent = NULL, *u, *v;
	edge_t *e;

	if (!graph || !start || !target)
		return (NULL);
	dist = malloc(graph->nb_vertices * sizeof(int));
	visited = calloc(graph->nb_vertices, sizeof(char));
	parent = calloc(graph->nb_vertices, sizeof(vertex_t *));
	path = queue_create();
	if (!dist || !visited || !parent || !path)
		goto cleanup;
	init_dijkstra(graph, start, dist);
	while ((u = find_min_vertex(graph, dist, visited)) != NULL)
	{
		printf("Checking %s, distance from %s is %d\n",
		       u->content, start->content, dist[u->index]);
		visited[u->index] = 1;
		if (u == target)
			break;
		for (e = u->edges; e; e = e->next)
		{
			v = e->dest;
			if (!visited[v->index] &&
			    dist[u->index] + e->weight < dist[v->index])
			{
				dist[v->index] = dist[u->index] + e->weight;
				parent[v->index] = u;
			}
		}
	}
	if (dist[target->index] == INT_MAX ||
	    !build_dijkstra_path(target, parent, path))
	{
		queue_delete(path);
		path = NULL;
	}
cleanup:
	free(dist);
	free(visited);
	free(parent);
	return (path);
}
