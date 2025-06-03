/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:32 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/03 17:25:36 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

char	*ft_strndup(const char *s, int n)
{
	char	*copy;
	int		i;

	copy = (char *)malloc((n + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/*
int	main(void)
{
	printf("%s\n", ft_strdup("Mattia"));
	return (0);
}
*/
