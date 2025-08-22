/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:07:20 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/07 15:09:29 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_recogn_t(char *line)
{
	if (line[0] == 34)
		return (TOKEN_DQUOTE);
	else if (line[0] == 39)
		return (TOKEN_SQUOTE);
	else if (line[0] == 124)
		return (TOKEN_PIPE);
	else if (line[0] == 60)
	{
		if (line[0 + 1] == 60)
			return (TOKEN_HEREDOC);
		else
			return (TOKEN_REDIRECT_IN);
	}
	else if (line[0] == 62)
	{
		if (line[0 + 1] == 62)
			return (TOKEN_APPEND);
		else
			return (TOKEN_REDIRECT_OUT);
	}
	return (TOKEN_WORD);
}

int	ft_sdquote(t_token **token, char *line, t_token_type type)
{
	char	quote;
	int		i;

	i = 0;
	quote = line[i++];
	(*token)->value = ft_strdup_ch(line + i, quote);
	if (!(*token)->value)
		return (-1);
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
	{
		(*token)->type = type;
		i++;
	}
	else
		(*token)->type = TOKEN_UNCLOSEDQUOTES;
	(*token)->next = ft_new_token_node();
	if (!(*token)->next)
		return (-1);
	(*token) = (*token)->next;
	return (i);
}

int	ft_here_app(t_token **token, char *line, t_token_type type)
{
	int	i;

	i = 0;
	(*token)->value = ft_strndup(line, 2);
	if (!(*token)->value)
		return (-1);
	i += 2;
	(*token)->type = type;
	(*token)->next = ft_new_token_node();
	if (!(*token)->next)
		return (-1);
	(*token) = (*token)->next;
	return (i);
}

int	ft_redir_pipe(t_token **token, char *line, t_token_type type)
{
	int	i;

	i = 0;
	(*token)->value = ft_strndup(line, 1);
	if (!(*token)->value)
		return (-1);
	i += 1;
	(*token)->type = type;
	(*token)->next = ft_new_token_node();
	if (!(*token)->next)
		return (-1);
	(*token) = (*token)->next;
	return (i);
}

int	ft_word(t_token **token, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t'
		&& (ft_recogn_t(line + i) == TOKEN_WORD
			|| ft_recogn_t(line + i) == TOKEN_DQUOTE
			|| ft_recogn_t(line + i) == TOKEN_SQUOTE))
		i++;
	(*token)->value = ft_no_quote_strndup(line, i);
	if (!(*token)->value)
		return (-1);
	(*token)->type = TOKEN_WORD;
	(*token)->next = ft_new_token_node();
	if (!(*token)->next)
		return (-1);
	(*token) = (*token)->next;
	return (i);
}

/*
int	ft_nr_token(char *line)
{
	int				nr_token;
	t_token_type	type;
	char			quote;

	nr_token = 0;
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (!*line)
			break ;
		type = ft_recogn_t(line);
		if (type == TOKEN_DQUOTE || type == TOKEN_SQUOTE)
		{
			quote = *line++;
			while (*line && *line != quote)
				line++;
			if (*line == quote)
				line++ ;
			nr_token++;
		}
		else if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		{
			line += 2;
			nr_token++;
		}
		else if (type == TOKEN_REDIRECT_IN ||
			type == TOKEN_REDIRECT_OUT || type == TOKEN_PIPE)
		{
			line++;
			nr_token++;
		}
		else
		{
			while (*line && *line != ' ' &&
				ft_recogn_t(line) != TOKEN_WORD)
			{
				if (*line == '\'' || *line == '\"')
				{
					quote = *line++;
					while (*line && *line != quote)
						line++;
					if (*line == quote)
						line++;
				}
				else
					line++;
			}
			nr_token++;
		}
	}
	return (nr_token);
}
*/
