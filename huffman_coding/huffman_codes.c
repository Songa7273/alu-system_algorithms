#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "heap.h"

/**
 * print_codes - traverses Huffman tree and prints codes
 * @tree: current node
 * @code: buffer storing current code
 * @depth: current depth in tree
 */
static void print_codes(binary_tree_node_t *tree, char *code, int depth)
{
	symbol_t *symbol;

	if (!tree)
		return;

	symbol = (symbol_t *)tree->data;

	/* Leaf node */
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
 * huffman_codes - builds Huffman tree and prints codes
 * @data: array of characters
 * @freq: array of frequencies
 * @size: size of arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[256];

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	print_codes(root, code, 0);

	return (1);
}
