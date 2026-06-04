#include <stdio.h>
#include "heap.h"

int int_cmp(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}

int main(void)
{
	heap_t *heap;
	int arr[] = {34, 2, 45, 23, 76};
	size_t i;
	int *extracted;

	heap = heap_create(int_cmp);
	if (!heap)
		return (1);

	for (i = 0; i < 5; i++)
		heap_insert(heap, &arr[i]);

	extracted = heap_extract(heap);
	printf("Extracted: %d\n", *extracted);
	printf("Heap size: %lu\n", heap->size);

	return (0);
}
