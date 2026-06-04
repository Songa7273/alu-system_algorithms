#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two minimum nodes from the
 * priority queue and inserts their merged parent node
 * @priority_queue: pointer to the heap
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *first;
	binary_tree_node_t *second;
	binary_tree_node_t *parent;
	binary_tree_node_t *new_symbol_node;
	symbol_t *new_symbol;
	symbol_t *s1;
	symbol_t *s2;

	if (!priority_queue || !priority_queue->root)
		return (0);

	/* extract two smallest nodes */
	first = heap_extract(priority_queue);
	if (!first)
		return (0);

	second = heap_extract(priority_queue);
	if (!second)
	{
		/* put back first if second extraction fails */
		heap_insert(priority_queue, first);
		return (0);
	}

	/* get symbol data from extracted nodes */
	s1 = (symbol_t *)((binary_tree_node_t *)first->data)->data;
	s2 = (symbol_t *)((binary_tree_node_t *)second->data)->data;

	/* create merged symbol */
	new_symbol = malloc(sizeof(symbol_t));
	if (!new_symbol)
		return (0);

	new_symbol->data = -1;
	new_symbol->freq = s1->freq + s2->freq;

	/* create node for symbol */
	new_symbol_node = binary_tree_node(NULL, new_symbol);
	if (!new_symbol_node)
	{
		free(new_symbol);
		return (0);
	}

	/* create parent node that holds the subtree */
	parent = binary_tree_node(NULL, new_symbol_node);
	if (!parent)
	{
		free(new_symbol_node);
		free(new_symbol);
		return (0);
	}

	/* attach children */
	parent->left = first;
	parent->right = second;
	first->parent = parent;
	second->parent = parent;

	/* insert new tree back into heap */
	if (!heap_insert(priority_queue, parent))
		return (0);

	return (1);
}
