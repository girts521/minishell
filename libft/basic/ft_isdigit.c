/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:53 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/19 15:36:40 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isdigit_str(char *str)
{
	while (*str)
	{
		if (*str <= '0' || *str >= '9')
			return (0);
		str++;
	}
	return (1);
}

// int	main(void)
// {
// 	printf("%d", ft_isdigit_str("12345 gfud"));
// 	return 0;
// }
