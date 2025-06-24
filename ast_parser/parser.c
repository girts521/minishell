#include "ast_parser.h"

t_ast	*parser(t_token *tokens)
{
	t_ast	*current_node;
	t_token	*previous_token;
	t_token	*token_head;
	t_ast	*root;

	current_node = create_ast_node();
	root = current_node;
	token_head = tokens;
	previous_token = NULL;
	while (tokens)
	{
		validate_token(tokens, previous_token, root, token_head);
		if (tokens->type == TOKEN_EOF)
			break ;
		if (tokens->type >= 0 && tokens->type <= 2)
			handle_command(tokens, current_node);
		if (tokens->type > 3 && tokens->type < 8)
			tokens = handle_redirect(tokens, current_node);
		if (tokens->type == TOKEN_PIPE)
			current_node = handle_pipe(&root, current_node);
		previous_token = tokens;
		tokens = tokens->next;
	}
	return (root);
}

// int	main(void)
// {
// 	t_ast	*root;
// 	t_token	*tokens1;
//
// 	tokens1 = get_test_input_11_tokens();
// 	root = parser(tokens1);
// 	print_ast(root);
// 	free_token_list(tokens1);
// 	cleanup(root);
// 	return (1);
// 
/*
 */
