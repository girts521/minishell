/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:15:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/12 15:44:18 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token_node(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->type = TOKEN_EOF;
	new->next = NULL;
	return (new);
}

int	ft_select_token(t_token **token, char *line, t_token_type type)
{
	int	move;

	move = 0;
	if (type == TOKEN_DQUOTE || type == TOKEN_SQUOTE)
		return (ft_sdquote(token, line, type));
	else if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
	{
		move = ft_here_app(token, line, type);
		if (move != 2)
			return (-1);
	}
		else if (type == TOKEN_REDIRECT_IN ||
		type == TOKEN_REDIRECT_OUT || type == TOKEN_PIPE)
	{
		move = ft_redir_pipe(token, line, type);
		if (move != 1)
			return (-1);
	}
	else
		return (ft_word(token, line));
	return (move);
}

void	ft_populate_token_list(t_token *token, char *line)
{
	t_token_type	type;
	int				move;

	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (!*line)
			break ;
		type = ft_recogn_t(line);
		move = ft_select_token(&token, line, type);
		if (move == -1)
			return ;
		line += move;
	}
}

/*
t_token	*tokenize_line(char *line, t_env *env)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);

	return (token);
}

t_token	*ft_create_token_list(char *line)
{
	t_token	*token_list;

	token_list = malloc(sizeof(t_token));
	ft_populate_token_list(token_list, line);
	return (token_list);
}
*/
