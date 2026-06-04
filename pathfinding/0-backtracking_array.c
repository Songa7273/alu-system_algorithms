#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"

/* Directions */
#define RIGHT 0
#define BOTTOM 1
#define LEFT 2
#define TOP 3

/**
 * is_valid - check if cell is valid
 */
static int is_valid(char **map, int rows, int cols,
                    int x, int y, char **visited)
{
	if (x < 0 || y < 0 || x >= rows || y >= cols)
		return 0;
	if (map[x][y] == '1')
		return 0;
	if (visited[x][y])
		return 0;
	return 1;
}

/**
 * dfs - recursive backtracking search (C90 compliant)
 */
static queue_t *dfs(char **map, int rows, int cols,
                    int x, int y,
                    point_t const *target,
                    char **visited)
{
	queue_t *path;
	point_t *pt;
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	int i;
	int nx;
	int ny;

	printf("Checking coordinates [%d, %d]\n", x, y);

	visited[x][y] = 1;

	/* base case */
	if (x == target->x && y == target->y)
	{
		path = queue_create();
		if (!path)
			return NULL;

		pt = malloc(sizeof(point_t));
		if (!pt)
			return NULL;

		pt->x = x;
		pt->y = y;
		enqueue(path, pt);

		return path;
	}

	for (i = 0; i < 4; i++)
	{
		nx = x + dx[i];
		ny = y + dy[i];

		if (is_valid(map, rows, cols, nx, ny, visited))
		{
			path = dfs(map, rows, cols, nx, ny, target, visited);

			if (path)
			{
				pt = malloc(sizeof(point_t));
				if (!pt)
					return NULL;

				pt->x = x;
				pt->y = y;

				queue_push_front(path, pt);
				return path;
			}
		}
	}

	return NULL;
}

/**
 * backtracking_array - entry point
 */
queue_t *backtracking_array(char **map, int rows, int cols,
                             point_t const *start,
                             point_t const *target)
{
	char **visited;
	queue_t *result;
	int i;

	visited = malloc(sizeof(char *) * rows);
	if (!visited)
		return NULL;

	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(char));
		if (!visited[i])
			return NULL;
	}

	result = dfs(map, rows, cols,
	             start->x, start->y,
	             target,
	             visited);

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return result;
}
