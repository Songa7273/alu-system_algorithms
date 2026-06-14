#include "pathfinding.h"

/**
 * backtrack_grid - Recursive helper function using backtracking over grid.
 * @map: Pointer to a read-only 2D map array.
 * @rows: Number of rows.
 * @cols: Number of columns.
 * @curr: Current structural coordinates.
 * @target: Target destination coordinates.
 * @visited: Tracking array for visited coordinates.
 * @path: The collection queue holding path structures.
 *
 * Return: 1 if target path is resolved, 0 otherwise.
 */
int backtrack_grid(char **map, int rows, int cols, point_t const *curr,
		   point_t const *target, char *visited, queue_t *path)
{
	point_t dirs[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	point_t *step, next;
	int i;

	if (curr->x < 0 || curr->x >= cols || curr->y < 0 || curr->y >= rows)
		return (0);
	if (visited[curr->y * cols + curr->x] || map[curr->y][curr->x] == '1')
		return (0);

	printf("Checking coordinates [%d, %d]\n", curr->x, curr->y);
	visited[curr->y * cols + curr->x] = 1;

	if (curr->x == target->x && curr->y == target->y)
	{
		step = malloc(sizeof(point_t));
		if (!step)
			return (0);
		step->x = curr->x;
		step->y = curr->y;
		queue_push_front(path, step);
		return (1);
	}

	for (i = 0; i < 4; i++)
	{
		next.x = curr->x + dirs[i].x;
		next.y = curr->y + dirs[i].y;

		if (backtrack_grid(map, rows, cols, &next, target, visited, path))
		{
			step = malloc(sizeof(point_t));
			if (!step)
				return (0);
			step->x = curr->x;
			step->y = curr->y;
			queue_push_front(path, step);
			return (1);
		}
	}
	return (0);
}

/**
 * backtracking_array - Finds first valid path via array backtracking.
 * @map: Pointer to a read-only 2D array.
 * @rows: Map row dimensions.
 * @cols: Map column dimensions.
 * @start: Starting point node pointer.
 * @target: Finishing point node pointer.
 *
 * Return: Alloc queue pathway if valid, NULL on failure.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path;
	char *visited;

	if (!map || !start || !target || rows <= 0 || cols <= 0)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(rows * cols, sizeof(char));
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}

	if (!backtrack_grid(map, rows, cols, start, target, visited, path))
	{
		free(visited);
		queue_delete(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
