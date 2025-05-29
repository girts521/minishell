/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:47:00 by mmagrin           #+#    #+#             */
/*   Updated: 2024/11/28 15:09:45 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_hex(unsigned int nbr)
{
	char	*base;
	char	c;

	base = "0123456789ABCDEF";
	if (nbr >= 16)
		ft_put_hex(nbr / 16);
	c = base[nbr % 16];
	write(1, &c, 1);
}

int	hex_digit_counter(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 16;
		count++;
	}
	return (count);
}

int	ft_printf_xx(unsigned int nbr)
{
	int	printed_chars;

	printed_chars = 0;
	if (nbr == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_put_hex(nbr);
	printed_chars += hex_digit_counter(nbr);
	return (printed_chars);
}
