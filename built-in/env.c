/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:33 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/06/26 18:37:50 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_envp(t_env *env)
{
	char	**envp;
	char	*joined;
	int		i;

	i = 0;
	t_env *tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		joined = ft_strjoin(env->key, "=");              // "KEY="
		envp[i] = ft_strjoin(joined, env->value);        // "KEY=VALUE"
		free(joined);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	ft_env(char **args, t_env *env)
{
	char	*command;
	char	**envp;
	
	command = NULL;
	if (!args[1])
	{
		while(env && env->key && env->value)
		{
			ft_printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	else if (args[1])
	{
		command = ft_strjoin("/bin/", args[1]);
		if (!command)
			return (1);
		envp = ft_env_to_envp(env);
		if (!envp)
		{
			free(command);
			return (1);
		}
		if (execve(command, args, envp) == -1)
		{
			ft_printf("minishell: env: '%s': No such file or directory\n", args[1]);
			free(command);
			ft_free_pointertopointer(envp);
			exit(127);
		}
	}
	return (0);
}