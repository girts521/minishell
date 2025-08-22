/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:04:38 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/07 14:08:45 by mmagrin          ###   ########.fr       */
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
			return (splitted_paths);
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_full_path(char *cmd, char **paths, int i)
{
	char	*full_path;
	char	*prefix;

	prefix = ft_strjoin(paths[i], "/");
	full_path = ft_strjoin(prefix, cmd);
	free(prefix);
	if (access(full_path, X_OK) == 0)
	{
		ft_free_pointertopointer(paths);
		return (full_path);
	}
	free(full_path);
	return (NULL);
}

int	ft_controll_get_command(char *cmd)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
		return (1);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (2);
		return (1);
	}
	return (0);
}

char	*ft_get_commandpath(t_env *env, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;
	int		code;

	code = ft_controll_get_command(cmd);
	if (code == 1)
		return (NULL);
	if (code == 2)
		return (ft_strdup(cmd));
	paths = ft_split_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_get_full_path(cmd, paths, i);
		if (full_path)
			return (full_path);
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
