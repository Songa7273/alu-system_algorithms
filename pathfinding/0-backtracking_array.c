#include "pathfinding.h"

/**
 * add_point - add a point to the path queue
 * @path: queue storing path
 * @p: point to add
 */
static void add_point(queue_t *path, point_t p)
{
	point_t *copy;

	copy = malloc(sizeof(point_t));
	if (!copy)
		return;

	*copy = p;
	enqueue(path, copy);
}

/**
 * dfs - depth first search for pathfinding
 * @grid: map grid
 * @rows: number of rows
 * @cols: number of columns
 * @current: current position
 * @goal: target position
 * @visited: visited matrix
 * @path: queue storing path
 *
 * Return: 1 if path found, 0 otherwise
 */
static int dfs(char **grid, int rows, int cols,
		point_t current, point_t goal,
		int **visited, queue_t *path)
{
	int dx[4] = {1, -1, 0, 0};
	int dy[4] = {0, 0, 1, -1};
	int i;

	if (current.x == goal.x && current.y == goal.y)
	{
		add_point(path, current);
		return (1);
	}

	if (visited[current.x][current.y])
		return (0);

	visited[current.x][current.y] = 1;
	add_point(path, current);

	for (i = 0; i < 4; i++)
	{
		point_t next;

		next.x = current.x + dx[i];
		next.y = current.y + dy[i];

		if (next.x >= 0 && next.y >= 0 &&
			next.x < rows && next.y < cols &&
			grid[next.x][next.y] == '0')
		{
			if (dfs(grid, rows, cols, next, goal, visited, path))
				return (1);
		}
	}

	return (0);
}

/**
 * backtracking_array - finds path using DFS backtracking
 * @grid: map grid
 * @rows: number of rows
 * @cols: number of columns
 * @start: starting position
 * @goal: target position
 *
 * Return: queue containing path, or NULL on failure
 */
queue_t *backtracking_array(char **grid, int rows, int cols,
				point_t start, point_t goal)
{
	queue_t *path;
	int **visited;
	int i;

	path = create_queue();
	if (!path)
		return (NULL);

	visited = malloc(sizeof(int *) * rows);
	if (!visited)
		return (NULL);

	for (i = 0; i < rows; i++)
		visited[i] = calloc(cols, sizeof(int));

	dfs(grid, rows, cols, start, goal, visited, path);

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return (path);
}
