/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gikarcev <gikarcev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:31:41 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/22 19:39:15 by gikarcev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_number = 0;

void	parse_execute(char *input, t_shell *shell, struct sigaction *sa_quit)
{
	t_ast	*root;
	t_token	*tokens;

	tokens = set_tokens(input, shell);
	root = parser(tokens);
	if (!root || !tokens)
	{
		cleanup(root, input, tokens);
		return ;
	}
	execute_ast(root, shell, sa_quit);
	add_history(input);
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

int	check_quotes(char *input)
{
	int		i;
	int		j;
	char	search;

	i = 0;
	j = 0;
	while (input[i])
	{
		search = input[i];
		if (input[i] == 39 || input[i] == 34)
		{
			j = i + 1;
			while (input[j] && input[j] != search)
				j++;
			if (input[j] && input[j] == search)
				i = j;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	main_help(t_shell *shell, char *input, struct sigaction sa_quit)
{
	g_signal_number = 0;
	input = readline("$> ");
	if (handle_exit(input) == 1)
		return (1);
	if (check_quotes(input) == 1)
	{
		validate_unclosedquotes();
		rl_on_new_line();
		free(input);
		return (0);
	}
	parse_execute(input, shell, &sa_quit);
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
		if (main_help(shell, input, sa_quit) == 1)
			break ;
		else
			continue ;
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
