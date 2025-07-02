/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:35:26 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/07/02 15:36:20 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_controll_token(char **args)
{
	int	i;
	int	y;

	y = 1;
	while (args[y])
	{
		if (args[y][0] != '_' && ft_isalpha(args[y][0]) != 1)
			return (1);
		i = 1;
		while (args[y][i] != '\0' && args[y][i] != '=')
		{
			if (args[y][i] != '_' && ft_isalnum(args[y][i]) != 1)
				return (1);
			i++;
		}
		y++;
	}
	return (0);
}