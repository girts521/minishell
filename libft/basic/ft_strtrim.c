/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:43:58 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

char	*ft_trimmed_len(int start, int end, char const *s1)
{
	char	*trimmed_str;
	int		i;
	int		len;

	if (start > end)
		return (ft_strdup(""));
	len = end - start + 1;
	trimmed_str = malloc((len + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trimmed_str[i] = s1[start];
		i++;
		start++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimmed_s1;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] != '\0')
	{
		if (ft_isin(s1[start], set) == 1)
			start++;
		else
			break ;
	}
	end = ft_strlen(s1) - 1;
	while (s1[end] > 0)
	{
		if (ft_isin(s1[end], set) == 1)
			end--;
		else
			break ;
	}
	trimmed_s1 = ft_trimmed_len(start, end, s1);
	return (trimmed_s1);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("", ""));
	return (0);
}
*/
