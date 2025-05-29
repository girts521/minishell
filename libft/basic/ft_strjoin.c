/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:54:33 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstr;
	int		len_join;
	int		i;
	int		j;

	len_join = ft_strlen(s1) + ft_strlen(s2);
	joinstr = malloc((len_join + 1) * sizeof(char));
	if (!joinstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		joinstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		joinstr[i + j] = s2[j];
		j++;
	}
	joinstr[i + j] = '\0';
	return (joinstr);
}
/*
int	main (void)
{
	printf("%s\n", ft_strjoin("Mattia ", "Magrin"));
	return (0);
}
*/
