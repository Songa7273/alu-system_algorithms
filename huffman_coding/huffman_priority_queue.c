#include "heap.h"
#include "huffman.h"
#include <stdlib.h>

/**
 * create_nested_node - creates a nested binary tree node
 * @symbol: pointer to symbol
 *
 * Return: pointer to binary_tree_node_t or NULL
 */
static binary_tree_node_t *create_nested_node(symbol_t *symbol)
{
	return (binary_tree_node(NULL, symbol));
}

/**
 * cmp_nested - compares two nested heap nodes
 * @a: first node
 * @b: second node
 *
 * Return: difference based on frequency
 */
static int cmp_nested(void *a, void *b)
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
 * Return: pointer to heap or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *nested;
	binary_tree_node_t *heap_node;
	symbol_t *symbol;
	size_t i;

	heap = heap_create(cmp_nested);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
			return (NULL);

		nested = create_nested_node(symbol);
		if (!nested)
			return (NULL);

		heap_node = binary_tree_node(NULL, nested);
		if (!heap_node)
			return (NULL);

		heap_insert(heap, heap_node);
	}

	return (heap);
}
