#include "huffman.h"
#include <stdlib.h>

/**
 * symbol_create - creates a symbol_t structure
 * @data: character
 * @freq: frequency
 *
 * Return: pointer to new symbol or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol;

	symbol = malloc(sizeof(symbol_t));
	if (!symbol)
		return (NULL);

	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
