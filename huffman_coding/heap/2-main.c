#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

int int_cmp(void *p1, void *p2)
{
	int *a = p1;
	int *b = p2;
	return (*a - *b);
}

int main(void)
{
	heap_t *heap;
	int values[] = {34, 2, 45, 23, 76};
	size_t i;

	heap = heap_create(int_cmp);
	if (!heap)
		return (1);

	for (i = 0; i < 5; i++)
	{
		heap_insert(heap, &values[i]);
		printf("Inserted: %d\n", values[i]);
	}

	printf("Heap size: %lu\n", heap->size);

	return (0);
}
