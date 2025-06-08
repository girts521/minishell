#include "minishell.h"

t_ast	*parser(t_token *tokens)
{
	t_ast	*current_node;
	t_ast	*root;

	current_node = create_ast_node();
	root = current_node;
	while (tokens)
	{
		printf("%s", tokens->value);
		if (tokens->type >= 0 && tokens->type <= 2)
			handle_command(tokens, current_node);
		if (tokens->type > 3 && tokens->type < 8)
		{
			handle_redirect(tokens, current_node);
			if (tokens->next)
				tokens = tokens->next;
		}
		if (tokens->type == TOKEN_PIPE)
		{
			current_node = handle_pipe(&root, current_node);
		}
		tokens = tokens->next;
	}
	printf("\n");
	return (root);
}

int	main(void)
{
	t_ast	*root;
	t_token	*tokens1;

	tokens1 = get_test_input_10_tokens();
	root = parser(tokens1);
	print_ast(root);
	free_token_list(tokens1);
	return (1);
}
