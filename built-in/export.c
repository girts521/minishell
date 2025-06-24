/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:07:11 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/24 16:09:00 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_controll_token(t_token *token)
{
	int	i;

	while (token)
	{
		if (token->value[0] != '_' && ft_isalpha(token->value[0]) != 1)
			return (1);
		i = 1;
		while (token->value[i] != '\0' && token->value[i] != '=')
		{
			if (token->value[i] != '_' && ft_isalnum(token->value[i]) != 1)
				return (1);
			i++;
		}
		token = token->next;
	}
	return (0);
}

char	*ft_extract_key(t_token *token)
{
	char	*new_var;
	int		i;

	i = 0;
	while (token->value[i] != '\0' && token->value[i] != '=')
		i++;
	new_var = ft_strndup(token->value, i);
	return (new_var);
}

char	*ft_extract_value_export(t_token *token)
{
	char	*new_value;
	int		i;

	i = 0;
	if (ft_isin('=', token->value) != 1)
		return (NULL);
	while (token->value[i] != '\0' && token->value[i] != '=')
		i++;
	i++;
	new_value = ft_strdup(token->value + i);
	return (new_value);
}

void	ft_add_var_value(t_token *token, t_env *env)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_extract_key(token);
	new_node->value = ft_extract_value_export(token);
	if (!new_node->value)
		new_node->value = ft_strdup("''");
	new_node->next = NULL;
	while (env->next != NULL)
		env = env->next;
	env = new_node;
}

void	ft_export(t_token *token, t_env *env)
{
	if (ft_controll_token(token) == 1)
		return ;
	while (token)
	{
		ft_add_var_value(token, env);
		token = token->next;
	}
}
