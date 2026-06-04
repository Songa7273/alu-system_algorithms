#include <stdio.h>
#include "huffman.h"

int main(void)
{
	symbol_t *s1;
	symbol_t *s2;

	s1 = symbol_create('d', 3);
	s2 = symbol_create('H', 98);

	if (!s1 || !s2)
		return (1);

	printf("Symbol: data(%c) frequency(%lu)\n", s1->data, s1->freq);
	printf("Symbol: data(%c) frequency(%lu)\n", s2->data, s2->freq);

	return (0);
}
