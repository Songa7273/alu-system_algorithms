#include "pathfinding.h"

/**
 * add_point - store point in path
 */
static void add_point(queue_t *path, point_t p)
{
	point_t *copy = malloc(sizeof(point_t));

	if (!copy)
		return;

	*copy = p;
	enqueue(path, copy);
}

/**
 * BFS node
 */
typedef struct bfs_node_s
{
	point_t p;
	point_t parent;
	int has_parent;
} bfs_node_t;

/**
 * backtracking_array - BFS shortest path
 */
queue_t *backtracking_array(char **grid, int rows, int cols,
				point_t start, point_t goal)
{
	queue_t *queue = create_queue();
	queue_t *path = create_queue();
	int **visited;
	point_t dirs[4] = {{1,0},{-1,0},{0,1},{0,-1}};
	int i, x, y;

	visited = malloc(sizeof(int *) * rows);
	for (i = 0; i < rows; i++)
		visited[i] = calloc(cols, sizeof(int));

	enqueue(queue, &start);

	while (queue->front)
	{
		point_t *cur = dequeue(queue);

		if (cur->x == goal.x && cur->y == goal.y)
		{
			add_point(path, *cur);
			break;
		}

		if (visited[cur->x][cur->y])
			continue;

		visited[cur->x][cur->y] = 1;
		add_point(path, *cur);

		for (i = 0; i < 4; i++)
		{
			x = cur->x + dirs[i].x;
			y = cur->y + dirs[i].y;

			if (x >= 0 && y >= 0 && x < rows && y < cols
				&& grid[x][y] == '0')
			{
				point_t *next = malloc(sizeof(point_t));

				next->x = x;
				next->y = y;

				enqueue(queue, next);
			}
		}
	}

	free_queue(queue);

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return (path);
}
