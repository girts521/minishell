/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:07:26 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/05 17:23:24 by mmagrin          ###   ########.fr       */
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

char	*ft_find_home(t_env *env)
{
	char	*target;

	while (ft_strcmp(env->key, "HOME") != 0)
	{
		env = env->next;
		if (!env)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
	}
	target = env->value;
	return (target);
}

int	ft_cd(char **args, t_env *env)
{
	char	*target;

	if (args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (!args[1])
		args[1] = ft_find_home(env);
	target = args[1];
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
