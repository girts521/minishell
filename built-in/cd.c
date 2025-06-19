/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:07:26 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/19 18:26:56 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_oldpwd(t_env *env)
{
	t_env	*head;
	char	*pwd_dup;

	head = env;
	while (env && ft_strcmp(env->key, "PWD") != 0)
		env = env->next;
	pwd_dup = ft_strdup(env->value);
	env = head;
	while (env && ft_strcmp(env->key, "OLDPWD") != 0)
		env = env->next;
	if (env)
	{
		free(env->value);
		env->value = pwd_dup;
	}
}

int	ft_set_pwd(t_env *env)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
	{
		perror("minishell: cd");
		return (1);
	}
	while (env && ft_strcmp(env->key, "PWD") != 0)
		env = env->next;
	if (env)
	{
		free(env->value);
		env->value = ft_strdup(cwd);
	}
	return (0);
}

char	*ft_target_path(t_token *token, t_env *env)
{
	char	*target;

	if (!token)
	{
		while (ft_strcmp(env->key, "HOME") != 0)
		{
			env = env->next;
			if (!env)
			{
				ft_printf("minishell: cd: HOME not set\n");
				return (NULL);
			}
		}
		target = env->value;
	}
	else
		target = token->value;
	return (target);
}

int	ft_cd(t_token *token, t_env *env)
{
	char	*target;

	if (token->next)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	target = ft_target_path(token, env);
	if (!target)
		return (1);
	ft_set_oldpwd(env);
	if (chdir(target) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	if (ft_set_pwd(env) == 1)
		return (1);
	return (0);
}
