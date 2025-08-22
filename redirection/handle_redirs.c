/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:25:32 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/22 17:42:02 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_append(t_ast *node, long redirc)
{
	char	*dest;
	int		dest_fd;

	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (dest_fd < 0)
	{
		perror(dest);
		return (1);
	}
	dup2(dest_fd, STDOUT_FILENO);
	close(dest_fd);
	return (0);
}

int	handle_redir_out(t_ast *node, long redirc)
{
	char	*dest;
	int		dest_fd;

	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (dest_fd < 0)
	{
		perror(dest);
		return (1);
	}
	dup2(dest_fd, STDOUT_FILENO);
	close(dest_fd);
	return (0);
}

int	handle_redir_in(t_ast *node, long redirc)
{
	char	*dest;
	int		dest_fd;

	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_RDONLY);
	if (dest_fd < 0)
	{
		perror(dest);
		return (1);
	}
	dup2(dest_fd, STDIN_FILENO);
	close(dest_fd);
	return (0);
}

int	check_redir_type(t_redirection_type redir_type)
{
	if (redir_type == REDIR_IN)
	{
		if (handle_redir_in(node, redirc) == 1)
			return (1);
	}
	else if (redir_type == REDIR_OUT)
	{
		if (handle_redir_out(node, redirc) == 1)
			return (1);
	}
	else if (redir_type == REDIR_APPEND)
	{
		if (handle_redir_append(node, redirc) == 1)
			return (1);
	}
	return (0);
}

int	handle_redirs(t_ast *node)
{
	t_redirection_type	redir_type;
	long				redirc;

	redirc = 0;
	if (node->data.command_node.redirc == 0)
		return (0);
	redir_type = node->data.command_node.redirection[redirc];
	while (redir_type)
	{
		if (check_redir_type(redir_type) == 1)
			return (1);
		redirc++;
		redir_type = node->data.command_node.redirection[redirc];
	}
	return (0);
}
