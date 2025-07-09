/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:41:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/08 17:57:38 by mmagrin          ###   ########.fr       */
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

void	ft_select_builtin(char **args, t_env *env, int builtins_check)
{
	if (builtins_check == 1)
		ft_echo(args);
	else if (builtins_check == 2)
		ft_cd(args, env);
	else if (builtins_check == 3)
		ft_pwd();
	else if (builtins_check == 4)
		ft_export(args, env);
	else if (builtins_check == 5)
		ft_unset(args, &env);
	else if (builtins_check == 6)
		ft_env(args, env);
	else if (builtins_check == 7)
		ft_exit(args, env);
}
