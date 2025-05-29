/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:41:02 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		len;
	int		i;

	len = ft_strlen(s);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
/*
int	main(void)
{
	printf("%s\n", ft_strdup("Mattia"));
	return (0);
}
*/
