/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:10:51 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/24 17:29:34 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_env(t_token *token, t_env *env)
{
	ft_free_token_list(token);
	ft_free_env(env);
}

long	ft_help_math(t_token *token)
{
	long	status;

	status = 0;
	if (!token)
		return (status);
	status = ft_atoi(token->value);
	status = status % 256;
	if (status < 0)
		status += 256;
	return (status);
}

int	ft_exit(t_token *token, t_env *env)
{
	long	sign;

	sign = 0;
	ft_printf("exit\n");
	if (token && token->next)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (token && (token->value[0] == '-' || token->value[0] == '+'))
		sign = 1;
	if (token && ft_isdigit_str(token->value + sign) != 1)
	{
		ft_printf("minishell: exit: %s: ", token->value);
		ft_printf("numeric argument required\n");
		ft_free_token_env(token, env);
		exit (255);
	}
	sign = ft_help_math(token);
	ft_free_token_env(token, env);
	exit (sign);
}
