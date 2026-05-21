#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * add_vertex_end - adds a vertex at the end of the list
 * @head: pointer to head of vertex list
 * @new: new vertex to add
 *
 * Return: pointer to added vertex
 */
static vertex_t *add_vertex_end(vertex_t **head, vertex_t *new)
{
	vertex_t *tmp;
	vertex_t *last;

	tmp = *head;
	last = NULL;

	while (tmp)
	{
		last = tmp;
		tmp = tmp->next;
	}

	if (last == NULL)
		*head = new;
	else
		last->next = new;

	return (new);
}

/**
 * graph_add_vertex - adds a vertex to a graph
 * @graph: pointer to graph
 * @str: string to store in vertex
 *
 * Return: pointer to new vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new, *tmp;

	if (graph == NULL || str == NULL)
		return (NULL);

	tmp = graph->vertices;
	while (tmp)
	{
		if (strcmp(tmp->content, str) == 0)
			return (NULL);
		tmp = tmp->next;
	}

	new = malloc(sizeof(vertex_t));
	if (new == NULL)
		return (NULL);

	new->content = strdup(str);
	if (new->content == NULL)
	{
		free(new);
		return (NULL);
	}

	new->edges = NULL;
	new->next = NULL;

	new->index = graph->nb_vertices;

	add_vertex_end(&graph->vertices, new);

	graph->nb_vertices++;

	return (new);
}
