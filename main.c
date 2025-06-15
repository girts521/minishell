#include "minishell.h"

int	main(void)
{
	t_ast	*root;
	t_token	*tokens;
	char	*input;

	tokens = ft_new_token_node();
	while (1)
	{
		input = readline("$> ");
		if (input == NULL)
		{
			printf("EOF...Quiting!");
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
			break ;
		ft_populate_token_list(tokens, input);
		root = parser(tokens);
		print_ast(root);
		execute_ast(root);
		ft_free_token_list(tokens);
		cleanup(root);
	}
	return (1);
}
