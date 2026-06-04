#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct binary_tree_node_s
{
	struct binary_tree_node_s *parent;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	void *data;
} binary_tree_node_t;

typedef struct heap_s
{
	binary_tree_node_t *root;
	size_t size;
	int (*data_cmp)(void *, void *);
} heap_t;

heap_t *heap_create(int (*data_cmp)(void *, void *));

#endif
