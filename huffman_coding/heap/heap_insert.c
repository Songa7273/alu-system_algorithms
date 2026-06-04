#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - swaps data between two nodes
 * @a: first node
 * @b: second node
 */
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp = a->data;

	a->data = b->data;
	b->data = tmp;
}

/**
 * heapify_up - restores min heap property
 * @node: node to heapify
 * @heap: heap structure
 */
static void heapify_up(binary_tree_node_t *node, heap_t *heap)
{
	while (node->parent &&
	       heap->data_cmp(node->parent->data, node->data) > 0)
	{
		swap_data(node, node->parent);
		node = node->parent;
	}
}

/**
 * insert_bfs - finds insertion spot using BFS
 * @heap: heap
 * @node: new node
 */
static void insert_bfs(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t **queue, *tmp;
	size_t front = 0, rear = 0;

	queue = malloc(sizeof(binary_tree_node_t *) * (heap->size + 2));
	if (!queue)
		return;

	queue[rear++] = heap->root;

	while (front < rear)
	{
		tmp = queue[front++];

		if (!tmp->left)
		{
			tmp->left = node;
			node->parent = tmp;
			break;
		}
		else
			queue[rear++] = tmp->left;

		if (!tmp->right)
		{
			tmp->right = node;
			node->parent = tmp;
			break;
		}
		else
			queue[rear++] = tmp->right;
	}

	free(queue);
}

/**
 * heap_insert - inserts a value in a Min Binary Heap
 * @heap: pointer to heap
 * @data: data to insert
 *
 * Return: pointer to inserted node or NULL
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node;

	if (!heap || !data)
		return (NULL);

	node = binary_tree_node(NULL, data);
	if (!node)
		return (NULL);

	if (!heap->root)
	{
		heap->root = node;
		heap->size++;
		return (node);
	}

	insert_bfs(heap, node);
	heapify_up(node, heap);

	heap->size++;

	return (node);
}
