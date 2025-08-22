/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gikarcev <gikarcev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:13 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/22 19:23:20 by gikarcev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	y;
	int	no_nl;

	if (!args[1])
	{
		ft_printf("\n");
		return ;
	}
	no_nl = 0;
	i = 1;
	while (args[i][0] == '-')
	{
		y = 1;
		while (args[i][y] == 'n')
			y++;
		if (args[i][y] != '\0')
			break ;
		no_nl = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		i++;
		if (args[i])
			ft_printf(" ");
	}
	if (no_nl != 1)
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
