/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:13 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/24 16:29:52 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_echo(char **args)
{
	int	i;

	i = 1;
	while (*args[i])
	{
		if (ft_recogn_t(*args[i]) == 1 || ft_recogn_t == 2)
		
		ft_printf("%s", *args[i]);
	}
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
