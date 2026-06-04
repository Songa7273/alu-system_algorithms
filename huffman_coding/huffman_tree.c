#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - builds a Huffman tree
 * @data: array of characters
 * @freq: array of frequencies
 * @size: size of the arrays
 *
 * Return: pointer to the root of the Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *root;

	if (!data || !freq || size == 0)
		return (NULL);

	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
		return (NULL);

	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	root = heap_extract(priority_queue);

	heap_delete(priority_queue, NULL);

	if (!root)
		return (NULL);

	return (root);
}
