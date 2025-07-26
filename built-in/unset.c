/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:44:24 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/07/26 16:18:08 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_controll_s_token(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '_' && ft_isalpha(arg[i]) != 1)
		return (1);
	i = 1;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (arg[i] != '_' && ft_isalnum(arg[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_help_unset(char *arg, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;
	
	prev = NULL;
	tmp = *env;
	while (tmp)
	{
		if(ft_strcmp(arg, tmp->key) == 0)
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (ft_controll_s_token(args[i]) == 1)
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			ft_help_unset(args[i], env);
		i++;
	}
	return (status);
}