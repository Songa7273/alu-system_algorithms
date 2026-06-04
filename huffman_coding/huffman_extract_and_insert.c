#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *first;
	binary_tree_node_t *second;
	binary_tree_node_t *parent;
	symbol_t *s1;
	symbol_t *s2;
	symbol_t *new_symbol;

	if (!priority_queue || !priority_queue->root)
		return (0);

	first = heap_extract(priority_queue);
	if (!first)
		return (0);

	second = heap_extract(priority_queue);
	if (!second)
	{
		heap_insert(priority_queue, first);
		return (0);
	}

	/* ✅ CORRECT: direct symbol access */
	s1 = (symbol_t *)first->data;
	s2 = (symbol_t *)second->data;

	if (!s1 || !s2)
		return (0);

	new_symbol = malloc(sizeof(symbol_t));
	if (!new_symbol)
	{
		heap_insert(priority_queue, first);
		heap_insert(priority_queue, second);
		return (0);
	}

	new_symbol->data = -1;
	new_symbol->freq = s1->freq + s2->freq;

	parent = binary_tree_node(NULL, new_symbol);
	if (!parent)
	{
		free(new_symbol);
		heap_insert(priority_queue, first);
		heap_insert(priority_queue, second);
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
