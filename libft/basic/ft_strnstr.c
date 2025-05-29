/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:29:12 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	j;
	size_t	i;

	if (*little == '\0')
		return (big);
	j = 0;
	while (big[j] != '\0' && j < len)
	{
		i = 0;
		while ((big[j + i] == little[i]) && ((j + i) < len))
		{
			if (little[i + 1] == '\0')
				return (&big[j]);
			i++;
		}
		j++;
	}
	return (0);
}
