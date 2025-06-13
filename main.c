#include "minishell.h"

int	main(void)
{
	t_ast	*root;
	t_token	*tokens1;

	tokens1 = get_test_input_5_tokens();
	root = parser(tokens1);
	print_ast(root);
	free_token_list(tokens1);
	cleanup(root);
	return (1);
}
