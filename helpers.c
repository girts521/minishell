/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:35:53 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/22 18:10:25 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exceve_use(t_shell *shell, char **args, char *command_node_value)
{
	char	**envp;
	char	*command;

	command = ft_get_commandpath(shell->env, command_node_value);
	if (!command)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		shell->last_exit_code = 127;
		return (127);
	}
	envp = ft_env_to_envp(shell->env);
	execve(command, args, envp);
	ft_free_pointertopointer(envp);
	free(command);
	command = NULL;
	return (0);
}

int	ft_is_valid_env_char(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

void	set_tokens(char *input, t_shell *shell,	t_token	*tokens)
{
	t_token	*current_token;
	t_token	*previous_token;

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
}
