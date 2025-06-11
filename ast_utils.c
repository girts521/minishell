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

void cleanup(t_ast *root)
{
	//TODO
	//node->command_node->redirection (t_redirection_type)
	//node->command_node->redir_dest (char **)
	//node->command_node->args (char **)
	//node itself t_ast
	int i;

	i = 0;
	while (root)
	{
		if (root->type == COMMANDop) {
		
		}
	}
	
}
