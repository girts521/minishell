/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:07:20 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/03 18:50:53 by mmagrin          ###   ########.fr       */
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

t_token	*ft_new_token_node(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->type = -1;
	new->next = NULL;
	return (new);
}

// int	ft_nr_token(char *line)
// {
// 	int				nr_token;
// 	t_token_type	type;
// 	char			quote;

// 	nr_token = 0;
// 	while (*line)
// 	{
// 		while (*line == ' ' || *line == '\t')
// 			line++;
// 		if (!*line)
// 			break ;
// 		type = ft_recogn_t(line);
// 		if (type == TOKEN_DQUOTE || type == TOKEN_SQUOTE)
// 		{
// 			quote = *line++;
// 			while (*line && *line != quote)
// 				line++;
// 			if (*line == quote)
// 				line++ ;
// 			nr_token++;
// 		}
// 		else if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
// 		{
// 			line += 2;
// 			nr_token++;
// 		}
// 		else if (type == TOKEN_REDIRECT_IN ||
// 			type == TOKEN_REDIRECT_OUT || type == TOKEN_PIPE)
// 		{
// 			line++;
// 			nr_token++;
// 		}
// 		else
// 		{
// 			while (*line && *line != ' ' &&
// 				ft_recogn_t(line) != TOKEN_WORD)
// 			{
// 				if (*line == '\'' || *line == '\"')
// 				{
// 					quote = *line++;
// 					while (*line && *line != quote)
// 						line++;
// 					if (*line == quote)
// 						line++;
// 				}
// 				else
// 					line++;
// 			}
// 			nr_token++;
// 		}
// 	}
// 	return (nr_token);
// }
