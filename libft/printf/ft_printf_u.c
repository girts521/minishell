/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:59:18 by mmagrin           #+#    #+#             */
/*   Updated: 2024/11/28 15:13:27 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnb(unsigned int num)
{
	if (num >= 10)
	{
		ft_putnb(num / 10);
		num = num % 10;
	}
	if (num < 10)
	{
		num = num + 48;
		write(1, &num, 1);
	}
}

int	ft_printf_u(unsigned int num)
{
	int				printed_chars;
	unsigned int	nbr;

	printed_chars = 0;
	nbr = num;
	if (num == 0)
		printed_chars++;
	else
	{
		while (num > 0)
		{
			num = num / 10;
			printed_chars++;
		}
	}
	ft_putnb(nbr);
	return (printed_chars);
}
