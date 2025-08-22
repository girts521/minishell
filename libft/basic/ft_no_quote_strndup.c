/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_quote_strndup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:58:12 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/07 14:43:20 by mmagrin          ###   ########.fr       */
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
			quote = s[i++];
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
