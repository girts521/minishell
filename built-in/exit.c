/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:10:51 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/26 17:08:54 by mattiamagri      ###   ########.fr       */
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

int	ft_exit(char **args, t_env *env)
{
	long	sign;

	sign = 0;
	ft_printf("exit\n");
	if (args[1] && args[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (args[1] && (args[1][0] == '-' || args[1][0] == '+'))
		sign = 1;
	if (args[1] && ft_isdigit_str(args[1] + sign) != 1)
	{
		ft_printf("minishell: exit: %s: ", args[1]);
		ft_printf("numeric argument required\n");
		ft_free_pointertopointer(args);
		exit (255);
	}
	sign = ft_help_math(args[1]);
	ft_free_token_env(args, env);
	exit (sign);
}
