/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:10:51 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/23 17:32:18 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_env(char **args, t_env *env)
{
	ft_free_pointertopointer(args);
	ft_free_env(env);
}

long	ft_help_math(char *arg)
{
	long	status;

	status = 0;
	if (!arg)
		return (status);
	status = ft_atoi(arg);
	status = status % 256;
	if (status < 0)
		status += 256;
	return (status);
}

int	ft_exit(char **args, t_shell *shell)
{
	shell->last_exit_code = 0;
	ft_printf("exit\n");
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (args[1] && (args[1][0] == '-' || args[1][0] == '+'))
		shell->last_exit_code = 1;
	if (args[1] && ft_isdigit_str(args[1] + shell->last_exit_code) != 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		ft_free_pointertopointer(args);
		shell->last_exit_code = 255;
		exit (255);
	}
	shell->last_exit_code = ft_help_math(args[1]);
	ft_free_token_env(args, shell->env);
	exit (shell->last_exit_code);
}