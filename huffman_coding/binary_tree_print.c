#include <stdio.h>
#include "heap.h"

/**
 * print_tree - helper function to print a binary tree
 */
static void print_tree(const binary_tree_node_t *root, int space,
	int (*print_data)(char *, void *))
{
	char buffer[1024];
	int i;

	if (!root)
		return;

	space += 5;

	print_tree(root->right, space, print_data);

	printf("\n");
	for (i = 5; i < space; i++)
		printf(" ");

	print_data(buffer, root->data);
	printf("%s\n", buffer);

	print_tree(root->left, space, print_data);
}

/**
 * binary_tree_print - prints a binary tree (Huffman heap version)
 */
void binary_tree_print(const binary_tree_node_t *tree,
	int (*print_data)(char *, void *))
{
	print_tree(tree, 0, print_data);
}
