#include "heap.h"
#include "huffman.h"
#include <stdlib.h>

/**
 * symbol_cmp - compares two symbols inside heap nodes
 */
static int symbol_cmp(void *a, void *b)
{
	symbol_t *sa = (symbol_t *)a;
	symbol_t *sb = (symbol_t *)b;

	return ((int)(sa->freq - sb->freq));
}

/**
 * huffman_priority_queue - builds priority queue
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	size_t i;

	heap = heap_create(symbol_cmp);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
			return (NULL);

		/* IMPORTANT: store symbol_t directly in heap node */
		heap_insert(heap, symbol);
	}

	return (heap);
}
