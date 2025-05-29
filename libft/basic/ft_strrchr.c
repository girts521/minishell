/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:01:25 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*flag;
	unsigned char	ch;

	flag = NULL;
	ch = (unsigned char)c;
	while (*s != '\0')
	{
		if ((unsigned char)*s == ch)
			flag = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return ((char *)flag);
}
