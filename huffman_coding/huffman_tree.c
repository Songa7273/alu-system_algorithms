#include "huffman.h"
#include "heap.h"

/**
 * huffman_tree - Builds a complete Huffman tree from character frequencies.
 * @data: Array of characters of size size.
 * @freq: Array containing the associated frequencies of size size.
 * @size: Size of the data and freq arrays.
 *
 * Return: Pointer to the root node of the Huffman tree, or NULL if it fails.
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *huffman_root;

	if (!data || !freq || size == 0)
		return (NULL);

	/* Populate your priority queue min-heap wrapper */
	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
		return (NULL);

	/* Loop extracting & combining the two min frequencies until 1 is left */
	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	/* Grab the last standing metadata payload node */
	huffman_root = (binary_tree_node_t *)priority_queue->root->data;

	/* Delete the priority queue shell structure safely */
	heap_delete(priority_queue, NULL);

	return (huffman_root);
}
