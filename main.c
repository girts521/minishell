#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	execution(t_ast *root)
{
	int	child;
	int	status;

	child = fork();
	if (child == -1)
		perror("Failed to fork a child!\n");
	else if (child == 0)
	{
		execute_ast(root);
		exit(0);
	}
	else
		waitpid(child, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_ast	*root;
	t_token	*tokens;
	t_env	*env;
	char	*input;

	(void)argc;
	(void)**argv;
	env = ft_init_env(envp);
	(void)env;
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
		tokens = ft_new_token_node();
		ft_populate_token_list(tokens, input);
		root = parser(tokens);
		print_ast(root);
		execution(root);
		rl_on_new_line();
		ft_free_token_list(tokens);
		cleanup(root);
	}
	return (1);
}
