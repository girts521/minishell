/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:07:26 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/07 16:54:08 by mattiamagri      ###   ########.fr       */
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

char	*ft_target_path(char *arg, t_env *env)
{
	char	*target;

	if (!arg[1])
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
		target = arg;
	return (target);
}

int	ft_cd(char **args, t_env *env)
{
	char	*target;

	if (args[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	target = ft_target_path(args[1], env);
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
