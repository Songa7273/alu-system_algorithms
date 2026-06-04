#include <stdlib.h>
#include "heap.h"

/**
 * swap_data - swaps node data
 */
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

/**
 * get_node - finds insertion parent using binary path
 */
static binary_tree_node_t *get_node(heap_t *heap, size_t index)
{
	binary_tree_node_t *node;
	size_t mask;

	node = heap->root;
	mask = 1UL << (sizeof(size_t) * 8 - 2);

	while (mask > 1)
	{
		if (index & mask)
			node = node->right;
		else
			node = node->left;
		mask >>= 1;
	}

	return (node);
}

/**
 * heap_insert - inserts a value in a Min Binary Heap
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *parent;
	size_t index;

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

	index = heap->size + 1;
	parent = get_node(heap, index >> 1);

	node->parent = parent;

	if (!(index & 1))
		parent->left = node;
	else
		parent->right = node;

	while (node->parent &&
	       heap->data_cmp(node->parent->data, node->data) > 0)
	{
		swap_data(node, node->parent);
		node = node->parent;
	}

	heap->size++;
	return (node);
}
