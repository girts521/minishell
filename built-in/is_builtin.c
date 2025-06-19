/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:41:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/18 17:42:18 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 1)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 1)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 1)
		return (1);
	else if (ft_strcmp(cmd, "export") == 1)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 1)
		return (1);
	else if (ft_strcmp(cmd, "env") == 1)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 1)
		return (1);
	return (0);
}
