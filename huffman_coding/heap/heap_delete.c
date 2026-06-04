#include "heap.h"
#include <stdlib.h>

/**
 * free_nodes - frees all nodes in a binary tree
 * @node: root node
 * @free_data: function to free node data
 *
 * Return: void
 */
static void free_nodes(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	free_nodes(node->left, free_data);
	free_nodes(node->right, free_data);

	if (free_data)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - deletes a Min Binary Heap
 * @heap: pointer to heap
 * @free_data: function to free node data (can be NULL)
 *
 * Return: void
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	free_nodes(heap->root, free_data);
	free(heap);
}
