#include <stdlib.h>
#include "huffman.h"

/**
 * binary_tree_delete - deletes an entire tree
 * @tree: root of tree
 */
void binary_tree_delete(binary_tree_node_t *tree)
{
	symbol_t *symbol;

	if (!tree)
		return;

	binary_tree_delete(tree->left);
	binary_tree_delete(tree->right);

	symbol = (symbol_t *)tree->data;
	free(symbol);
	free(tree);
}
