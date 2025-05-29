/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:34:32 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

int	ft_digit_count(int n)
{
	int	d;

	if (n == 0)
		return (1);
	d = 0;
	while (n > 0)
	{
		n = n / 10;
		d++;
	}
	return (d);
}

int	ft_turnpos(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

int	ft_isnegsign(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 1;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_isnegsign(n);
	n = ft_turnpos(n);
	i = i + ft_digit_count(n);
	nbr = malloc((i + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[i] = '\0';
	while (i > 0)
	{
		i--;
		if (n == 0 && nbr[i + 1] != '\0')
		{
			nbr[i] = '-';
			break ;
		}
		nbr[i] = n % 10 + '0';
		n = n / 10;
	}
	return (nbr);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(123456789));
	return (0);
}
*/
