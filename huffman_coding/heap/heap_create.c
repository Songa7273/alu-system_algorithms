#include <stdlib.h>
#include "heap.h"

/**
 * heap_create - Creates a Heap data structure
 * @data_cmp: Comparison function
 *
 * Return: Pointer to heap, or NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
    heap_t *heap;

    if (data_cmp == NULL)
        return (NULL);

    heap = malloc(sizeof(heap_t));
    if (heap == NULL)
        return (NULL);

    heap->root = NULL;
    heap->size = 0;
    heap->data_cmp = data_cmp;

    return (heap);
}
