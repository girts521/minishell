/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:13 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/14 18:33:56 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_echo(char **args)
{
	int	i;
	int	no_nl;

	no_nl = 0;
	i = 1;
	while (args[i][0] == '-' && args[i][1] == 'n')
	{
		no_nl = 1;
		i++;
	}
	while (args[i])
	{
		if (ft_recogn_t(args[i]) == 1 || ft_recogn_t(args[i]) == 2)
		{
			int	y = 1;
			while(args[i][y] != 34 && args[i][y] != 39)
			{
				ft_printf("%c", args[i][y]);
				y++;
			}
		}
		else
			ft_printf("%s", args[i]);
		i++;
		if (args[i])
			ft_printf(" ");
	}
	if (!no_nl)
		ft_printf("\n");
}

/*
void	ft_echo(t_token *token)
{
	int	new_line;

	new_line = 1;
	while (token && ft_strcmp(token->value, "-n") == 0)
	{
		token = token->next;
		new_line = 0;
	}
	while (token && (
		token->type == TOKEN_WORD ||
		token->type == TOKEN_SQUOTE ||
		token->type == TOKEN_DQUOTE))
	{
		ft_printf("%s", token->value);
		if (token->next && (
			token->next->type == TOKEN_WORD ||
			token->next->type == TOKEN_SQUOTE ||
			token->next->type == TOKEN_DQUOTE))
			ft_printf(" ");
		token = token->next;
	}
	if (new_line)
		ft_printf("\n");
}
*/
