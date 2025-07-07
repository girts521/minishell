/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:33 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/07/07 17:24:40 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_envp(t_env *env)
{
	char	**envp;
	char	*joined;
	int		i;

	i = ft_envlst_size(env);
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		joined = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(joined, env->value);
		free(joined);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	ft_env_help(char **args, t_env *env)
{
	char	*command;
	char	**envp;

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
		return(127);
	}
	return (0);
}

int	ft_env(char **args, t_env *env)
{	
	int	check;
	
	if (!args[1])
	{
		while(env && env->key && env->value && env->next != NULL)
		{
			ft_printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	else if (args[1])
	{
		check = ft_env_help(args, env);
		if (check == 1)
			return (1);
		else if (check == 127)
			exit(127);
	}
	return (0);
}