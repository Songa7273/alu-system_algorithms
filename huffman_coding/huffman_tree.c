#include <stdlib.h>
#include "huffman.h"
#include "heap.h"

/**
 * frequency_compare - Stable frequency node comparison function for min-heap.
 * @p1: First payload pointer.
 * @p2: Second payload pointer.
 *
 * Return: Difference between frequencies.
 */
static int frequency_compare(void *p1, void *p2)
{
	binary_tree_node_t *node1 = (binary_tree_node_t *)p1;
	binary_tree_node_t *node2 = (binary_tree_node_t *)p2;
	symbol_t *sym1 = (symbol_t *)node1->data;
	symbol_t *sym2 = (symbol_t *)node2->data;

	return (sym1->freq - sym2->freq);
}

/**
 * stable_extract_and_insert - Merges two minimum nodes from heap with stable order.
 * @priority_queue: Pointer to the min-heap.
 *
 * Return: 1 on success, 0 on failure.
 */
static int stable_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left, *right, *parent;
	symbol_t *symbol;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	left = (binary_tree_node_t *)heap_extract(priority_queue);
	right = (binary_tree_node_t *)heap_extract(priority_queue);
	if (!left || !right)
		return (0);

	symbol = malloc(sizeof(symbol_t));
	if (!symbol)
		return (0);

	symbol->data = -1;
	symbol->freq = ((symbol_t *)left->data)->freq + ((symbol_t *)right->data)->freq;

	parent = binary_tree_node(NULL, symbol);
	if (!parent)
	{
		free(symbol);
		return (0);
	}

	parent->left = left;
	parent->right = right;
	left->parent = parent;
	right->parent = parent;

	if (heap_insert(priority_queue, parent) == NULL)
		return (0);

	return (1);
}

/**
 * huffman_tree - Builds a complete Huffman tree from character frequencies.
 * @data: Array of characters of size size.
 * @freq: Array containing the associated frequencies of size size.
 * @size: Size of the data and freq arrays.
 *
 * Return: Pointer to the root node of the Huffman tree, or NULL if it fails.
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *huffman_root;

	if (!data || !freq || size == 0)
		return (NULL);

	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
		return (NULL);

	/* Override the default heap data comparison rule with our stable tracker */
	priority_queue->data_cmp = frequency_compare;

	while (priority_queue->size > 1)
	{
		if (!stable_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	huffman_root = (binary_tree_node_t *)priority_queue->root->data;
	heap_delete(priority_queue, NULL);

	return (huffman_root);
}
