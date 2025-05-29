/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:37:29 by mmagrin           #+#    #+#             */
/*   Updated: 2024/11/27 17:15:16 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int num)
{
	if (num < 0)
	{
		write(1, "-", 1);
		num = num * -1;
	}
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	if (num < 10)
	{
		num = num + 48;
		write(1, &num, 1);
	}
}

int	ft_printf_d_i(int num)
{
	int	printed_chars;
	int	nbr;

	printed_chars = 0;
	nbr = num;
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (num < 0)
		printed_chars = 1;
	ft_putnbr(nbr);
	if (num == 0)
		printed_chars++;
	else
	{
		while (num > 0 || num < 0)
		{
			num = num / 10;
			printed_chars++;
		}
	}
	return (printed_chars);
}
