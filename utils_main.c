/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:04:38 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/07/24 12:14:46 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_paths(t_env *env)
{
	char	**splitted_paths;
	
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			splitted_paths = ft_split(env->value, ':');
			return(splitted_paths);
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_command_path(t_env *env, char *cmd)
{
	char	**paths;
	char	*prefix;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_split_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		prefix = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(prefix, cmd);
		free(prefix);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_pointertopointer(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_pointertopointer(paths);
	return (NULL);
}

void	ft_print_env(t_env *env)
{
	while (env)
	{
		if (env->key)
		{
			ft_printf("%s", env->key);
			if (env->value[0] != '\0')
				ft_printf("=%s", env->value);
			ft_printf("\n");
		}
		env = env->next;
	}
}