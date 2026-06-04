#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - builds full Huffman tree
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *root;

	if (!data || !freq || size == 0)
		return (NULL);

	heap = huffman_priority_queue(data, freq, size);
	if (!heap)
		return (NULL);

	while (heap->size > 1)
	{
		if (!huffman_extract_and_insert(heap))
		{
			heap_delete(heap, NULL);
			return (NULL);
		}
	}

	root = heap_extract(heap);

	heap_delete(heap, NULL);

	return (root);
}
