/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:00:40 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/07 14:25:48 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_expansion(t_token *token, char *key, char *value, int y)
{
	char	*pre;
	char	*post;
	char	*join_str;
	char	*tmp;
	int		prekey_len;

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

void	helping(t_shell *shell, t_token *token, int y)
{
	int		key_len;
	char	*value;
	char	*key;

	if (token->value[y + 1] == '?')
	{
		key = strdup("?");
		value = ft_itoa(shell->last_exit_code);
		ft_expansion(token, key, value, y);
		free(value);
	}
	else
	{
		key_len = ft_len_of_key(token->value + y + 1);
		key = ft_strndup(token->value + y + 1, key_len);
		value = ft_is_in_env(shell->env, key);
		if (value)
			ft_expansion(token, key, value, y);
		else
			ft_expansion(token, key, "", y);
	}
	free(key);
}

void	ft_expand_var(t_token *token, t_shell *shell)
{
	int		y;

	y = 0;
	while (token)
	{
		if (token->type == TOKEN_WORD || token->type == TOKEN_DQUOTE)
		{
			y = ft_isin('$', token->value);
			if (y != -1)
				helping(shell, token, y);
			y = ft_isin('$', token->value);
		}
		token = token->next;
	}
}
