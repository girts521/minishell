/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:09:14 by mmagrin           #+#    #+#             */
/*   Updated: 2024/11/28 15:07:08 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hexa_converter(unsigned long nbr)
{
	char	*base;
	char	c;

	base = "0123456789abcdef";
	if (nbr >= 16)
		hexa_converter(nbr / 16);
	c = base[nbr % 16];
	write(1, &c, 1);
}

int	hex_digit_count(unsigned long nbr)
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

int	ft_printf_p(void *ptr)
{
	unsigned long	nbr;
	int				printed_chars;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	nbr = (unsigned long)ptr;
	write(1, "0x", 2);
	printed_chars = 2;
	hexa_converter(nbr);
	printed_chars += hex_digit_count(nbr);
	return (printed_chars);
}
