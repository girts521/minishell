/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:34:23 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/07 16:50:22 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_create_node(void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_extract_key_env(content);
	new_node->value = ft_extract_value_env(content);
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

t_env	*ft_init_env(char *envp[])
{
	int		i;
	t_env	*env;
	t_env	*new;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new = ft_create_node(envp[i]);
		if (!new)
			return (NULL);
		ft_env_add_back(&env, new);
		i++;
	}
	return (env);
}
