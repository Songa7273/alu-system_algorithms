#include "huffman.h"

/**
 * compare_frequencies - compares two symbol nodes
 * @p1: first node
 * @p2: second node
 *
 * Return: comparison result
 */
int compare_frequencies(void *p1, void *p2)
{
	binary_tree_node_t *node1;
	binary_tree_node_t *node2;
	symbol_t *symbol1;
	symbol_t *symbol2;

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;

	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;

	if (symbol1->freq < symbol2->freq)
		return (-1);

	if (symbol1->freq > symbol2->freq)
		return (1);

	if (symbol1->data < symbol2->data)
		return (-1);

	if (symbol1->data > symbol2->data)
		return (1);

	return (0);
}

/**
 * huffman_priority_queue - creates a min-heap priority queue
 * @data: array of characters
 * @freq: array of frequencies
 * @size: size of arrays
 *
 * Return: pointer to heap, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

	heap = heap_create(compare_frequencies);
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

		if (!heap_insert(heap, node))
			return (NULL);
	}

	return (heap);
}
