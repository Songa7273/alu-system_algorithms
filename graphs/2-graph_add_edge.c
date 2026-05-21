#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * find_vertex - Finds a vertex in a graph by its content string
 * @graph: Pointer to the graph
 * @str: String to search for
 *
 * Return: Pointer to the matching vertex, or NULL if not found
 */
static vertex_t *find_vertex(graph_t *graph, const char *str)
{
	vertex_t *current;

	for (current = graph->vertices; current; current = current->next)
	{
		if (strcmp(current->content, str) == 0)
			return (current);
	}

	return (NULL);
}

/**
 * append_edge - Appends a new edge to the end of a vertex adjacency list
 * @source: Vertex receiving the new edge
 * @destination: Vertex pointed to by the new edge
 *
 * Return: 1 on success, 0 on failure
 */
static int append_edge(vertex_t *source, vertex_t *destination)
{
	edge_t *new_edge;
	edge_t *current;

	new_edge = malloc(sizeof(edge_t));
	if (!new_edge)
		return (0);

	new_edge->dest = destination;
	new_edge->next = NULL;

	if (!source->edges)
	{
		source->edges = new_edge;
		return (1);
	}

	current = source->edges;
	while (current->next)
		current = current->next;

	current->next = new_edge;
	return (1);
}

/**
 * remove_last_edge - Removes the last edge from a vertex adjacency list
 * @source: Vertex whose last edge should be removed
 */
static void remove_last_edge(vertex_t *source)
{
	edge_t *current;
	edge_t *previous;

	if (!source || !source->edges)
		return;

	if (!source->edges->next)
	{
		free(source->edges);
		source->edges = NULL;
		return;
	}

	previous = NULL;
	current = source->edges;
	while (current->next)
	{
		previous = current;
		current = current->next;
	}

	previous->next = NULL;
	free(current);
}

/**
 * graph_add_edge - Adds a directional or bidirectional edge between vertices
 * @graph: Pointer to the graph
 * @src: String identifying the source vertex
 * @dest: String identifying the destination vertex
 * @type: Type of connection to create
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   graph_edge_type_t type)
{
	vertex_t *source;
	vertex_t *destination;

	if (!graph || !src || !dest ||
	    (type != UNIDIRECTIONAL && type != BIDIRECTIONAL))
		return (0);

	source = find_vertex(graph, src);
	destination = find_vertex(graph, dest);
	if (!source || !destination)
		return (0);

	if (!append_edge(source, destination))
		return (0);

	if (type == BIDIRECTIONAL)
	{
		if (!append_edge(destination, source))
		{
			remove_last_edge(source);
			return (0);
		}
	}

	return (1);
}
