/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:05:29 by mmagrin           #+#    #+#             */
/*   Updated: 2025/03/11 15:51:05 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_freer(char *buffer)
{
	free (buffer);
	return (NULL);
}

void	ft_initializer(char **s)
{
	if (!s)
		return ;
	*s = malloc(1);
	if (!*s)
	{
		*s = NULL;
		return ;
	}
	(*s)[0] = '\0';
}

char	*ft_reader(int fd, char *buffer)
{
	char	*reader;
	char	*bigger_buffer;
	int		bytes;

	if (!buffer)
		ft_initializer(&buffer);
	reader = malloc(BUFFER_SIZE + 1);
	if (!reader)
		return (NULL);
	bytes = read(fd, reader, BUFFER_SIZE);
	while (bytes > 0)
	{
		reader[bytes] = '\0';
		bigger_buffer = ft_strjoin(buffer, reader);
		free (buffer);
		buffer = bigger_buffer;
		if (ft_strch(buffer, '\n') == 1)
			break ;
		bytes = read(fd, reader, BUFFER_SIZE);
	}
	free (reader);
	if (bytes < 0)
		return (ft_freer(buffer));
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*rest;

	buffer = ft_reader(fd, buffer);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
	{
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_extract_line(buffer);
	rest = ft_extract_rest(buffer);
	free (buffer);
	buffer = rest;
	return (line);
}

/*
int	main(int argc, char *argv[])
{
	char	*line;
	int		fd;

	if (argc < 2)
	{
		write(2, "error", 5);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "error opening", 13);
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (!line)
			break ;
		free (line);
	}
	close(fd);
	return (0);
}
*/
