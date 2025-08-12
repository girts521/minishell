/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:31:41 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/05 16:45:37 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_number = 0;

void	parse_execute(char *input, t_shell *shell, struct sigaction *sa_quit)
{
	t_ast	*root;
	t_token	*tokens;

	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, input);
	ft_expand_var(tokens, shell);
	root = parser(tokens);
	if (!root || !tokens)
	{
		cleanup(root, input, tokens);
		return ;
	}
	print_ast(root);
	execute_ast(root, shell, sa_quit);
	cleanup(root, input, tokens);
	rl_on_new_line();
}

int	handle_exit(char *input)
{
	if (input == NULL )
	{
		printf("EOF...Quiting!");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				*shell;
	char				*input;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	(void)argc;
	(void)**argv;
	prepare_signals(&sa_int, &sa_quit);
	shell = malloc(sizeof(t_shell));
	shell->env = ft_init_env(envp);
	shell->last_exit_code = 0;
	input = NULL;
	while (1)
	{
		g_signal_number = 0;
		input = readline("$> ");
		if (handle_exit(input) == 1)
			break ;
		add_history(input);
		parse_execute(input, shell, &sa_quit);
	}
	ft_free_env(shell->env);
	free(shell);
	clear_history();
	return (1);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	tests(argc, argv, envp);
// }
