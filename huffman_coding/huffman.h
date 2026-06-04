#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>
#include "heap.h"

/**
 * struct symbol_s - Huffman symbol
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/* symbol */
symbol_t *symbol_create(char data, size_t freq);

/* huffman */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);

#endif /* HUFFMAN_H */
