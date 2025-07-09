/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:10:10 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/07 16:50:40 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strch_i(char *str, char c)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*ft_extract_key_env(char *env_str)
{
	int		i;
	char	*key;

	i = ft_strch_i(env_str, '=');
	if (i == -1)
		return (NULL);
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, env_str, i + 1);
	return (key);
}

char	*ft_extract_value_env(char *env_str)
{
	char	*value;
	char	*ptr;

	ptr = ft_strchr(env_str, '=');
	if (!ptr)
		return (ft_strdup(""));
	value  = ft_strdup(ptr + 1);
	return (value);
}

void	ft_env_add_back(t_env **env, t_env *new)
{
	t_env *curr;

	if (!new)
		return ;
	if (!*env)
	{
		*env = new;
		return;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
