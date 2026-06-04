#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * compare_frequencies - compares two heap nodes
 * @p1: first node
 * @p2: second node
 *
 * Return: negative if p1 < p2, positive if p1 > p2
 */
int compare_frequencies(void *p1, void *p2)
{
	binary_tree_node_t *n1 = p1;
	binary_tree_node_t *n2 = p2;

	symbol_t *s1 = n1->data;
	symbol_t *s2 = n2->data;

	if (s1->freq != s2->freq)
		return (s1->freq - s2->freq);

	/* tie-breaker (VERY IMPORTANT FOR ALU) */
	return (s1->data - s2->data);
}

/**
 * huffman_priority_queue - builds min heap
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *node;
	symbol_t *symbol;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

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
