#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"

#define RIGHT 0
#define BOTTOM 1
#define LEFT 2
#define TOP 3
#define NUM_DIRECTIONS 4

/* ========================= */
/* QUEUE FUNCTIONS ONLY (NO STRUCTS HERE!) */
/* ========================= */

queue_t *queue_create(void)
{
	queue_t *q = malloc(sizeof(queue_t));

	if (!q)
		return NULL;

	q->front = NULL;
	q->rear = NULL;
	return q;
}

void enqueue(queue_t *q, void *data)
{
	queue_node_t *node = malloc(sizeof(queue_node_t));

	if (!q || !node)
		return;

	node->data = data;
	node->next = NULL;

	if (!q->rear)
	{
		q->front = q->rear = node;
		return;
	}

	q->rear->next = node;
	q->rear = node;
}

void *dequeue(queue_t *q)
{
	queue_node_t *tmp;
	void *data;

	if (!q || !q->front)
		return NULL;

	tmp = q->front;
	data = tmp->data;
	q->front = q->front->next;

	if (!q->front)
		q->rear = NULL;

	free(tmp);
	return data;
}

void queue_push_front(queue_t *q, void *data)
{
	queue_node_t *node = malloc(sizeof(queue_node_t));

	if (!q || !node)
		return;

	node->data = data;
	node->next = q->front;
	q->front = node;

	if (!q->rear)
		q->rear = node;
}

/* ========================= */
/* BACKTRACKING LOGIC */
/* ========================= */

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

static queue_t *dfs(char **map, int rows, int cols,
                    int x, int y,
                    point_t const *target,
                    char **visited)
{
	queue_t *path;
	point_t *pt;

	printf("Checking coordinates [%d, %d]\n", x, y);

	visited[x][y] = 1;

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

	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

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
