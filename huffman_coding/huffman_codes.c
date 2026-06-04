#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/**
 * free_tree - frees Huffman tree
 */
static void free_tree(binary_tree_node_t *tree)
{
	if (!tree)
		return;

	free_tree(tree->left);
	free_tree(tree->right);
	free(tree->data);
	free(tree);
}

/**
 * print_codes - DFS traversal
 */
static void print_codes(binary_tree_node_t *tree, char *code, int depth)
{
	symbol_t *symbol;

	if (!tree)
		return;

	symbol = tree->data;

	if (!tree->left && !tree->right)
	{
		code[depth] = '\0';
		printf("%c: %s\n", symbol->data, code);
		return;
	}

	code[depth] = '0';
	print_codes(tree->left, code, depth + 1);

	code[depth] = '1';
	print_codes(tree->right, code, depth + 1);
}

/**
 * huffman_codes - main function
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[1024];

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	print_codes(root, code, 0);
	free_tree(root);

	return (1);
}
