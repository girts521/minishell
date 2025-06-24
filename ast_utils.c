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

long	count_args(t_token *token)
{
	long	result;

	result = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type >= 0 && token->type < 3)
			result++;
		token = token->next;
	}
	return (result * sizeof(char *));
}

void	cleanup(t_ast *root)
{
	if (!root)
		return ;
	if (root->type == COMMAND_NODE)
	{
		if (root->data.command_node.redirection)
			free(root->data.command_node.redirection);
		if (root->data.command_node.redir_dest)
			free(root->data.command_node.redir_dest);
		free(root->data.command_node.args);
	}
	cleanup(root->left);
	cleanup(root->right);
	free(root);
}
