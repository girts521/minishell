#include "minishell.h"

//TODO:
//1. Error management, return if some input is wrong
//2. Memory management

t_ast	*parser(t_token *tokens)
{
	t_ast	*current_node;
	t_token	*previous_token;
	t_ast	*root;

	current_node = create_ast_node();
	root = current_node;
	while (tokens)
	{
		validate_token(tokens, previous_token);
		if (tokens->type == TOKEN_EOF)
			break ;
		if (tokens->type >= 0 && tokens->type <= 2)
			handle_command(tokens, current_node);
		if (tokens->type > 3 && tokens->type < 8)
		{
			handle_redirect(tokens, current_node);
			if (tokens->next)
				tokens = tokens->next;
		}
		if (tokens->type == TOKEN_PIPE)
			current_node = handle_pipe(&root, current_node);
		previous_token = tokens;
		tokens = tokens->next;
	}
	return (root);
}

int	main(void)
{
	t_ast	*root;
	t_token	*tokens1;

	tokens1 = get_test_input_4_tokens();
	root = parser(tokens1);
	print_ast(root);
	free_token_list(tokens1);
	return (1);
}
