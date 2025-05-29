/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:05:25 by mmagrin           #+#    #+#             */
/*   Updated: 2025/03/15 17:17:32 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strch(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

char	*ft_extract_rest(char *s1)
{
	int		i;
	int		y;
	char	*rest;

	i = 0;
	y = 0;
	while (s1[i] != '\n' && s1[i] != '\0')
		i++;
	if (s1[i] == '\0')
		return (NULL);
	while (s1[i + y] != '\0')
		y++;
	rest = malloc(y + 1);
	if (!rest)
		return (NULL);
	y = 0;
	while (s1[++i] != '\0')
		rest[y++] = s1[i];
	rest[y] = '\0';
	if (rest[0] == '\0')
	{
		free (rest);
		return (NULL);
	}
	return (rest);
}

char	*ft_extract_line(char *s1)
{
	int		i;
	int		y;
	char	*line;

	i = 0;
	while (s1[i] != '\n' && s1[i] != '\0')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	y = 0;
	while (s1[y] != '\n' && s1[y] != '\0')
	{
		line[y] = s1[y];
		y++;
	}
	if (ft_strch(s1, '\n') == 1)
	{
		line[y] = '\n';
		line[y + 1] = '\0';
	}
	else
		line[y] = '\0';
	return (line);
}

/*
int main(void)
{
	char	*rest;
	char	*line;
	int		i;
	char	c;

	rest = ft_extract_rest("ciao sono mattia piacere\n");
	line = ft_extract_line("ciao\n");
	i = 0;
	while (line[i] != '\0')
	{
		write (1, &line[i], 1);
		i++;
	}
	i = 0;
	while (rest[i] != '\0')
	{
		c = rest[i];
		write (1, &c, 1);
		i++;
	}
	return (0);
}
*/
