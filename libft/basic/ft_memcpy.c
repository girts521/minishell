/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:41:25 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char dest[] = "abcde";
	const char src[]  = "abcde";

	printf("Before memcpy dest = %s, src = %s\n", dest, src);
	memcpy(&dest[2], dest, 3);
	printf("After memcpy dest = %s, src = %s\n\n", dest, src);

	char des[] = "abcde";
	const char sr[]  = "abcde";

	printf("Before FT des = %s, sr = %s\n", des, sr);
	ft_memcpy(&des[2], des, 3);
	printf("After FT des = %s, sr = %s\n", des, sr);
	return(0);
}
*/
