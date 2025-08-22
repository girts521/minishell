/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:07:11 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/22 17:22:40 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_key_export(char *arg)
{
	char	*new_var;
	int		i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	new_var = ft_strndup(arg, i);
	return (new_var);
}

char	*ft_extract_value_export(char *arg)
{
	char	*new_value;
	int		i;

	i = 0;
	if (ft_isin('=', arg) == -1)
		return (NULL);
	while (arg[i] != '=')
		i++;
	i++;
	new_value = ft_strdup(arg + i);
	return (new_value);
}

int	ft_add_existing_key(char *arg, t_env *env)
{
	char	*key;
	char	*value;

	key = ft_extract_key_export(arg);
	value = ft_extract_value_export(arg);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			if (value)
				env->value = value;
			else
				env->value = ft_strdup("");
			free(key);
			return (1);
		}
		env = env->next;
	}
	free(key);
	free(value);
	return (0);
}

int	ft_add_var_value(char *arg, t_env *env)
{
	t_env	*new_node;
	int		already_exist;

	already_exist = ft_add_existing_key(arg, env);
	if (already_exist == 0)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (1);
		new_node->key = ft_extract_key_export(arg);
		new_node->value = ft_extract_value_export(arg);
		if (!new_node->value)
			new_node->value = ft_strdup("");
		new_node->next = NULL;
		while (env->next)
			env = env->next;
		env->next = new_node;
	}
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		ft_print_env(env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!ft_controll_token(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			ft_add_var_value(args[i], env);
		i++;
	}
	return (status);
}
