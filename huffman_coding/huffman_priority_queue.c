#include "heap.h"
#include "huffman.h"
#include <stdlib.h>

/**
 * symbol_cmp - compares two heap nodes by symbol frequency
 * @a: first node
 * @b: second node
 *
 * Return: difference between frequencies (min heap)
 */
static int symbol_cmp(void *a, void *b)
{
	binary_tree_node_t *na = (binary_tree_node_t *)a;
	binary_tree_node_t *nb = (binary_tree_node_t *)b;

	symbol_t *sa = (symbol_t *)na->data;
	symbol_t *sb = (symbol_t *)nb->data;

	return ((int)(sa->freq - sb->freq));
}

/**
 * huffman_priority_queue - builds a min heap (priority queue)
 * @data: array of characters
 * @freq: array of frequencies
 * @size: number of elements
 *
 * Return: pointer to created heap, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *node;
	symbol_t *symbol;
	size_t i;

	heap = heap_create(symbol_cmp);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
			return (NULL);

		node = binary_tree_node(NULL, symbol);
		if (!node)
			return (NULL);

		heap_insert(heap, node);
	}

	return (heap);
}
