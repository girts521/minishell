#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	t_ast	*root;
	t_token	*tokens;
	t_env	*env;
	char	*input;

	(void)argc;
	(void)**argv;
	env = ft_init_env(envp);
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
		add_history(input);
		tokens = ft_new_token_node();
		ft_populate_token_list(tokens, input);
		root = parser(tokens);
		print_ast(root);
		execute_ast(root, env);
		rl_on_new_line();
		ft_free_token_list(tokens);
//		cleanup(root);
//		ft_free_env(env);
	}
	return (1);
}
