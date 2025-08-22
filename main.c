/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:31:41 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/07 14:37:28 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_number = 0;

void	parse_execute(char *input, t_shell *shell, struct sigaction *sa_quit)
{
	t_ast	*root;
	t_token	*tokens;
	t_token *current_token;
	t_token *previous_token;

	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, input);
	ft_expand_var(tokens, shell);
	current_token = tokens;
	previous_token = NULL;
	while (current_token)
	{
		if (validate_token(current_token, previous_token) == 1)
		{
			cleanup(NULL, input, tokens);
			return ; 
		}
		previous_token = current_token;
		current_token = current_token->next;
	}
	root = parser(tokens);
	if (!root || !tokens)
	{
		cleanup(root, input, tokens);
		return ;
	}
	// print_ast(root);
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

int check_quotes(char *input)
{
	int i;
	int j;
	char search;

	i = 0;
	j = 0;
	while(input[i++])
	{
		search = input[i];
		if (input[i] == 39 || input[i] == 34) // '
		{
			j = i + 1;
			while (input[j] && input[j] != search)
				j++;
			if (input[j] && input[j] == search)
				i = j;
			else 
				return (1);
		}
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
		if (check_quotes(input) == 1)
		{
			validate_unclosedquotes();
			rl_on_new_line();
			free(input);
			continue ;
		}
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
