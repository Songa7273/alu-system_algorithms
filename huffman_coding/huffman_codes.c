#include <stdio.h>
#include "huffman.h"

/**
 * print_codes - prints Huffman codes
 * @tree: Huffman tree
 * @code: code buffer
 * @depth: current depth
 */
static void print_codes(binary_tree_node_t *tree,
	char *code, int depth)
{
	symbol_t *symbol;

	if (!tree)
		return;

	symbol = (symbol_t *)tree->data;

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
 * @data: array of chars
 * @freq: array of frequencies
 * @size: size of arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[1024];

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	print_codes(root, code, 0);

	binary_tree_delete(root);

	return (1);
}
