#include <stdio.h>
#include "heap.h"
#include "huffman.h"

int main(void)
{
	heap_t *pq;
	char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	size_t freq[] = {6, 11, 12, 13, 16, 36};
	size_t size = sizeof(data) / sizeof(data[0]);

	pq = huffman_priority_queue(data, freq, size);
	if (!pq)
	{
		printf("Failed\n");
		return (1);
	}

	printf("Priority queue created. Size: %lu\n", pq->size);

	return (0);
}
