#include "minishell.h"

//Creates a node with  empty values. 
//Used COMMAND_NODE as default, should 
//be overwritten later.
t_ast	*create_ast_node(void)
{
	t_ast	*node;

	node = (t_ast *)safe_calloc(1, sizeof(t_ast));
	node->type = COMMAND_NODE;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_ast(void)
{
	//TODO
}
