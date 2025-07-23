/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:41:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/23 16:32:30 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd, "export") == 0)
		return (4);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (5);
	else if (ft_strcmp(cmd, "env") == 0)
		return (6);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}

void	ft_select_builtin(char **args, t_shell *shell, int builtins_check)
{
	if (builtins_check == 1)
		ft_echo(args);
	else if (builtins_check == 2)
		shell->last_exit_code = ft_cd(args, shell->env);
	else if (builtins_check == 3)
		ft_pwd();
	else if (builtins_check == 4)
		shell->last_exit_code = ft_export(args, shell->env);
	else if (builtins_check == 5)
		shell->last_exit_code = ft_unset(args, &shell->env);
	else if (builtins_check == 6)
		shell->last_exit_code = ft_env(args, shell->env);
	else if (builtins_check == 7)
		shell->last_exit_code = ft_exit(args, shell);
}
