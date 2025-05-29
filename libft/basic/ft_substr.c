/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:51:34 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

size_t	ft_adjust_len(size_t str_len, unsigned int start, size_t len)
{
	if (start >= str_len)
		return (0);
	if (str_len - start < len)
		return (str_len - start);
	return (len);
}

char	*ft_allocate(size_t len)
{
	char	*sub_str;

	sub_str = malloc((len + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	return (sub_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	str_len;
	size_t	i;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	len = ft_adjust_len(str_len, start, len);
	sub_str = ft_allocate(len);
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
