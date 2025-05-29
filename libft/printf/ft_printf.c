/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:21:59 by mmagrin           #+#    #+#             */
/*   Updated: 2024/11/28 15:03:45 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	caller(int printed_chars, int i, const char *str, va_list args)
{
	i++;
	if (str[i] == 'c')
		printed_chars += ft_printf_c(va_arg(args, int));
	if (str[i] == 's')
		printed_chars += ft_printf_s(va_arg(args, char *));
	if (str[i] == 'p')
		printed_chars += ft_printf_p(va_arg(args, void *));
	if (str[i] == 'd' || str[i] == 'i')
		printed_chars += ft_printf_d_i(va_arg(args, int));
	if (str[i] == 'u')
		printed_chars += ft_printf_u(va_arg(args, unsigned int));
	if (str[i] == 'x')
		printed_chars += ft_printf_x(va_arg(args, unsigned int));
	if (str[i] == 'X')
		printed_chars += ft_printf_xx(va_arg(args, unsigned int));
	if (str[i] == 37)
	{
		write(1, "%", 1);
		printed_chars += 1;
	}
	return (printed_chars);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printed_chars;
	va_list	args;

	va_start(args, str);
	printed_chars = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 37)
		{
			printed_chars = caller(printed_chars, i, str, args);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			printed_chars++;
		}
		i++;
	}
	va_end(args);
	return (printed_chars);
}
/*
int	main(void)
{
	printf("nel %d avevo %i anni\n", 2010, 6);
	ft_printf("nel %d avevo %i anni\n", 2010, 6);
	return (0);
}
*/
