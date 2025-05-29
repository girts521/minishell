/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:57:40 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	nbr;

	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		sign = sign * -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	nbr = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - 48);
		nptr++;
	}
	return (nbr * sign);
}
