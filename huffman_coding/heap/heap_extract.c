#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - swaps data between two nodes
 * @a: first node
 * @b: second node
 *
 * Return: void
 */
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp = a->data;

	a->data = b->data;
	b->data = tmp;
}

/**
 * heapify_down - restores heap property after extraction
 * @node: root node to heapify
 * @heap: pointer to heap structure
 *
 * Return: void
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
 * get_last_node - finds last node in heap using BFS
 * @heap: pointer to heap
 *
 * Return: pointer to last node or NULL
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
 * heap_extract - extracts root of a Min Binary Heap
 * @heap: pointer to heap
 *
 * Return: pointer to extracted data or NULL on failure
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
