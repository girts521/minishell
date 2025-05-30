/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:15:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/30 18:45:13 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_line(char *line, t_env *env)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);

	return (token);
}

char	*ft_extract_token(char *line, t_token_type token)
{

}

char	**ft_split_token(char *line)
{
	char	**split_tokens;
	int		i;
	int		nr_token;

	nr_token = 0;
	nr_token = ft_nr_token(line);
	split_tokens = malloc(sizeof(char *) * nr_token);
	if (!split_tokens)
		return (NULL);
	
}
