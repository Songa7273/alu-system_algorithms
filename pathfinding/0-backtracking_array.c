#include <stdio.h>
#include <stdlib.h>

#include "pathfinding.h"

/**
 * backtrack - recursive search
 * @map: map
 * @rows: number of rows
 * @cols: number of columns
 * @x: current x coordinate (column)
 * @y: current y coordinate (row)
 * @target: target point
 * @visited: visited matrix
 * @path: path queue
 *
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack(char **map, int rows, int cols,
		int x, int y,
		point_t const *target,
		char **visited,
		queue_t *path)
{
	point_t *point;

	(void)rows;

	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return (0);

	if (map[y][x] != '0')
		return (0);

	if (visited[y][x])
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);

	visited[y][x] = 1;

	if (x == target->x && y == target->y)
	{
		point = malloc(sizeof(*point));
		if (!point)
			return (0);

		point->x = x;
		point->y = y;
		queue_push_front(path, point);

		return (1);
	}

	/* RIGHT */
	if (backtrack(map, rows, cols, x + 1, y,
				target, visited, path))
	{
		point = malloc(sizeof(*point));
		if (!point)
			return (0);

		point->x = x;
		point->y = y;
		queue_push_front(path, point);

		return (1);
	}

	/* BOTTOM */
	if (backtrack(map, rows, cols, x, y + 1,
				target, visited, path))
	{
		point = malloc(sizeof(*point));
		if (!point)
			return (0);

		point->x = x;
		point->y = y;
		queue_push_front(path, point);

		return (1);
	}

	/* LEFT */
	if (backtrack(map, rows, cols, x - 1, y,
				target, visited, path))
	{
		point = malloc(sizeof(*point));
		if (!point)
			return (0);

		point->x = x;
		point->y = y;
		queue_push_front(path, point);

		return (1);
	}

	/* TOP */
	if (backtrack(map, rows, cols, x, y - 1,
				target, visited, path))
	{
		point = malloc(sizeof(*point));
		if (!point)
			return (0);

		point->x = x;
		point->y = y;
		queue_push_front(path, point);

		return (1);
	}

	return (0);
}

/**
 * free_visited - frees visited matrix
 * @visited: matrix
 * @rows: number of rows
 */
static void free_visited(char **visited, int rows)
{
	int i;

	for (i = 0; i < rows; i++)
		free(visited[i]);

	free(visited);
}

/**
 * backtracking_array - finds first path using backtracking
 * @map: map
 * @rows: number of rows
 * @cols: number of columns
 * @start: start point
 * @target: target point
 *
 * Return: queue containing path or NULL
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start,
		point_t const *target)
{
	queue_t *path;
	char **visited;
	int i;

	if (!map || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = malloc(sizeof(char *) * rows);
	if (!visited)
	{
		free(path);
		return (NULL);
	}

	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(char));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);

			free(visited);
			free(path);
			return (NULL);
		}
	}

	if (!backtrack(map, rows, cols,
			start->x, start->y,
			target, visited, path))
	{
		free_visited(visited, rows);
		free(path);
		return (NULL);
	}

	free_visited(visited, rows);

	return (path);
}
