/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:15:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/03 18:50:41 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_populate_token_list(t_token *token, char *line)
{
	char			quote;
	t_token_type	type;
	int				i;
	char			*start;
	int				word_len;

	word_len = 0;
	i = 0;
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
			token->value = ft_strdup_ch(line, quote);
			if (!token->value)
				return ;
			while (*line && *line != quote)
				line++;
			if (*line == quote)
				line++ ;
			token->type = type;
			token->next = ft_new_token_node();
			if (!token->next)
				return ;
			token = token->next;
		}
		else if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		{
			token->value = ft_strndup(line, 2);
			if (!token->value)
				return ;
			line += 2;
			token->type = type;
			token->next = ft_new_token_node();
			if (!token->next)
				return ;
			token = token->next;
		}
		else if (type == TOKEN_REDIRECT_IN ||
			type == TOKEN_REDIRECT_OUT || type == TOKEN_PIPE)
		{
			token->value = ft_strndup(line, 1);
			if (!token->value)
				return ;
			line += 1;
			token->type = type;
			token->next = ft_new_token_node();
			if (!token->next)
				return ;
			token = token->next;
		}
		else
		{
			start = line;
			i = 0;
			while (*line != '\0' && *line != ' ' && *line != '\t' &&
				ft_recogn_t(line) == TOKEN_WORD)
				line++;
			word_len = line - start;
			token->value = ft_strndup(start, word_len);
			if (!token->value)
				return ;
			token->type = TOKEN_WORD;
			token->next = ft_new_token_node();
			if (!token->next)
				return ;
			token = token->next;
		}
	}
}

// t_token	*tokenize_line(char *line, t_env *env)
// {
// 	t_token	*token;

// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);

// 	return (token);
// }

// t_token	*ft_create_token_list(char *line)
// {
// 	t_token	*token_list;

// 	token_list = malloc(sizeof(t_token));
// 	ft_populate_token_list(token_list, line);
// 	return (token_list);
// }
