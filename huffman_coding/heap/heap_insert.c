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
 * heap_insert - inserts node in Min Heap
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t **queue;
	binary_tree_node_t *node, *tmp;
	size_t front, rear;

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

	queue[0] = heap->root;
	front = 0;
	rear = 1;

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

	/* bubble up */
	while (node->parent &&
	       heap->data_cmp(node->parent->data, node->data) > 0)
	{
		swap_data(node, node->parent);
		node = node->parent;
	}

	heap->size++;
	return (node);
}
