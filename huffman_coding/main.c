#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * int_cmp - compares two integers
 */
int int_cmp(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}

/**
 * print_int - prints integer
 */
int print_int(char *buffer, void *data)
{
	return sprintf(buffer, "(%03d)", *(int *)data);
}

/**
 * free_data - frees data (optional for heap_delete)
 */
void free_data(void *data)
{
	free(data);
}

int main(void)
{
	heap_t *heap;
	int *val;
	int i;
	int arr[] = {34, 2, 45, 23, 76};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	heap = heap_create(int_cmp);
	if (!heap)
		return (1);

	printf("Inserting values...\n");
	for (i = 0; i < (int)size; i++)
	{
		val = malloc(sizeof(int));
		if (!val)
			return (1);
		*val = arr[i];

		heap_insert(heap, val);
	}

	printf("Heap size: %lu\n", heap->size);

	printf("Extracting root...\n");
	val = heap_extract(heap);
	if (val)
		printf("Extracted: %d\n", *val);

	printf("Heap size after extract: %lu\n", heap->size);

	printf("Deleting heap...\n");
	heap_delete(heap, free_data);

	return (0);
}
