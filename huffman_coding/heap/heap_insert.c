#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - swaps data between two nodes
 */
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp = a->data;

	a->data = b->data;
	b->data = tmp;
}

/**
 * heap_insert - inserts value into Min Binary Heap
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *tmp, **queue;
	size_t front = 0, rear = 0;

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

	queue = malloc(sizeof(binary_tree_node_t *) * (heap->size + 2));
	if (!queue)
		return (NULL);

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

	while (node->parent &&
	       heap->data_cmp(node->parent->data, node->data) > 0)
	{
		swap_data(node, node->parent);
		node = node->parent;
	}

	heap->size++;

	return (node);
}
