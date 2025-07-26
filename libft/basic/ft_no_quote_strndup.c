/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_quote_strndup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:58:12 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/07/26 16:04:01 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

char	*ft_no_quote_strndup(char *s, int n)
{
	char	*dst;
	int		i;
	int		j;
	char	quote;

	dst = malloc(n + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			i++;
			while (i < n && s[i] != quote)
				dst[j++] = s[i++];
			if (i < n && s[i] == quote)
				i++;
		}
		else
			dst[j++] = s[i++];
	}
	dst[j] = '\0';
	return (dst);
}