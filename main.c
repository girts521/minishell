#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/history.h>

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_ast	*root;
	t_token	*tokens;
	t_env	*env;
	char	*input;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	(void)argc;
	(void)**argv;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
	env = ft_init_env(envp);
	input = NULL;
	while (1)
	{
		input = readline("$> ");
		if (input == NULL)
		{
			printf("EOF...Quiting!");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		if (ft_strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		tokens = ft_new_token_node();
		ft_populate_token_list(tokens, input);
		root = parser(tokens);
		// print_ast(root);
		execute_ast(root, env);
		free(input);
		ft_free_token_list(tokens);
		cleanup(root);
		rl_on_new_line();
	}
	ft_free_env(env);
	rl_clear_history();
	return (1);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	tests(argc, argv, envp);
// }
