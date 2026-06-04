#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

/**
 * struct binary_tree_node_s - Binary tree node
 * @parent: Pointer to parent node
 * @left: Pointer to left child
 * @right: Pointer to right child
 * @data: Pointer to stored data
 */
typedef struct binary_tree_node_s
{
	struct binary_tree_node_s *parent;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	void *data;
} binary_tree_node_t;

/**
 * struct heap_s - Min Binary Heap structure
 * @root: Pointer to root node
 * @size: Number of nodes in heap
 * @data_cmp: Function used to compare node data
 */
typedef struct heap_s
{
	binary_tree_node_t *root;
	size_t size;
	int (*data_cmp)(void *, void *);
} heap_t;

heap_t *heap_create(int (*data_cmp)(void *, void *));
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent,
	void *data);
binary_tree_node_t *heap_insert(heap_t *heap, void *data);

#endif /* HEAP_H */
