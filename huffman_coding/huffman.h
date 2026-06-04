#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>

/**
 * struct symbol_s - Huffman symbol
 * @data: character stored
 * @freq: frequency of character
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

symbol_t *symbol_create(char data, size_t freq);

#endif /* HUFFMAN_H */
