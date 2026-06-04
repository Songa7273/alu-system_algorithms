#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two minimum nodes and
 * inserts their merged parent node into the heap
 * @priority_queue: pointer to heap
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *first, *second, *parent;
	symbol_t *s1, *s2, *new_symbol;

	if (!priority_queue || !priority_queue->root)
		return (0);

	first = heap_extract(priority_queue);
	second = heap_extract(priority_queue);

	if (!first || !second)
		return (0);

	s1 = (symbol_t *)first->data;
	s2 = (symbol_t *)second->data;

	new_symbol = malloc(sizeof(symbol_t));
	if (!new_symbol)
		return (0);

	new_symbol->data = -1;
	new_symbol->freq = s1->freq + s2->freq;

	parent = binary_tree_node(NULL, new_symbol);
	if (!parent)
	{
		free(new_symbol);
		return (0);
	}

	parent->left = first;
	parent->right = second;
	first->parent = parent;
	second->parent = parent;

	if (!heap_insert(priority_queue, parent))
		return (0);

	return (1);
}
