/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:00:40 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/07/16 17:46:56 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_env_char(int c)
{
	if((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

int	ft_len_of_key(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && ft_is_valid_env_char(str[i]))
		i++;
	return (i);
}

char	*ft_is_in_env(t_env *env, char *key)
{
	while(env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_expansion(t_token *token, char *key, char *value)
{
	char	*pre;
	char	*post;
	char	*join_str;
	char	*tmp;
	int		y;
	int		prekey_len;

	y = ft_isin('$', token->value);
	pre = ft_strndup(token->value, y);
	tmp = ft_strjoin(pre, value);
	prekey_len = ft_strlen(key) + y + 1;
	post = ft_strdup(token->value + prekey_len);
	join_str = ft_strjoin(tmp, post);
	free(token->value);
	token->value = join_str;
	free(tmp);
	free(pre);
	free(post);
}

void	ft_expand_var(t_token *token, t_env *env)
{
	int		y;
	int		key_len;
	char	*value;
	char	*key;

	y = 0;
	while(token)
	{
		if (token->type == TOKEN_WORD || token->type == TOKEN_SQUOTE)
		{
			y = ft_isin('$', token->value);
			while (y != -1)
			{
				key_len = ft_len_of_key(token->value + y + 1);
				key = ft_strndup(token->value + y + 1, key_len);
				value = ft_is_in_env(env, key);
				if (value)
					ft_expansion(token, key, value);
				free(key);
				y = ft_isin('$', token->value);
			}
		}
		token = token->next;
	}
}