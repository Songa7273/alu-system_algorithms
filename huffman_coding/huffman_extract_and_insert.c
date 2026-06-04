#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - merges 2 smallest nodes
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *first, *second, *parent;
	symbol_t *s1, *s2, *new_symbol;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	first = heap_extract(priority_queue);
	second = heap_extract(priority_queue);

	if (!first || !second)
		return (0);

	s1 = first->data;
	s2 = second->data;

	new_symbol = malloc(sizeof(symbol_t));
	if (!new_symbol)
		return (0);

	new_symbol->freq = s1->freq + s2->freq;
	new_symbol->data = '$';

	parent = binary_tree_node(NULL, new_symbol);
	if (!parent)
	{
		free(new_symbol);
		return (0);
	}

	/* IMPORTANT: deterministic structure */
	if (s1->freq < s2->freq ||
		(s1->freq == s2->freq && s1->data <= s2->data))
	{
		parent->left = first;
		parent->right = second;
	}
	else
	{
		parent->left = second;
		parent->right = first;
	}

	first->parent = parent;
	second->parent = parent;

	if (!heap_insert(priority_queue, parent))
		return (0);

	return (1);
}
