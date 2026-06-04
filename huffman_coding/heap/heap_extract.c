#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - swaps node data
 */
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp = a->data;

	a->data = b->data;
	b->data = tmp;
}

/**
 * heapify_down - restores min heap property
 */
static void heapify_down(binary_tree_node_t *node, heap_t *heap)
{
	binary_tree_node_t *smallest, *left, *right;

	while (node)
	{
		smallest = node;
		left = node->left;
		right = node->right;

		if (left && heap->data_cmp(left->data, smallest->data) < 0)
			smallest = left;

		if (right && heap->data_cmp(right->data, smallest->data) < 0)
			smallest = right;

		if (smallest == node)
			break;

		swap_data(node, smallest);
		node = smallest;
	}
}

/**
 * get_last_node - BFS last node in heap
 */
static binary_tree_node_t *get_last_node(heap_t *heap)
{
	binary_tree_node_t **queue, *tmp, *last;
	size_t front = 0, rear = 0;

	queue = malloc(sizeof(binary_tree_node_t *) * heap->size);
	if (!queue)
		return (NULL);

	queue[rear++] = heap->root;
	last = NULL;

	while (front < rear)
	{
		tmp = queue[front++];
		last = tmp;

		if (tmp->left)
			queue[rear++] = tmp->left;
		if (tmp->right)
			queue[rear++] = tmp->right;
	}

	free(queue);
	return (last);
}

/**
 * heap_extract - extracts root of Min Binary Heap
 * @heap: heap to extract from
 *
 * Return: pointer to data or NULL
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last = get_last_node(heap);
	if (!last)
		return (NULL);

	heap->root->data = last->data;

	if (last->parent)
	{
		if (last->parent->left == last)
			last->parent->left = NULL;
		else
			last->parent->right = NULL;
	}

	free(last);

	heap->size--;

	heapify_down(heap->root, heap);

	return (data);
}
