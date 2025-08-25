/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:24:54 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/22 17:25:04 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_cleanup(t_list **dest_cleanup)
{
	t_list	*current_node;
	t_list	*next_node;

	current_node = *dest_cleanup;
	next_node = NULL;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		unlink((char *)current_node->content);
		free(current_node);
		current_node = next_node;
	}
}

void	write_temp_file(t_ast *node, int temp_file, int redirc)
{
	char	*delimiter;
	char	*line;
	int		delimiter_len;

	delimiter = node->data.command_node.redir_dest[redirc];
	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			perror("delimiter was not found!");
			break ;
		}
		if (ft_strlen(line) == delimiter_len + 1 && \
			ft_strncmp(line, delimiter, delimiter_len) == 0)
		{
			free(line);
			break ;
		}
		write(temp_file, line, ft_strlen(line));
		free(line);
	}
	close(temp_file);
}

char	*execute_heredoc(t_ast *node, long redirc)
{
	char	*dest;
	int		temp_file;
	char	*char_redir;

	char_redir = ft_itoa(redirc);
	dest = ft_strjoin("/tmp/minishell_heredoc_", char_redir);
	temp_file = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_file == -1)
	{
		free(dest);
		perror("Failed to open a temp file");
		return (NULL);
	}
	write_temp_file(node, temp_file, redirc);
	free(char_redir);
	return (dest);
}

void	handle_heredoc(t_ast *ast, t_list **dest_cleanup)
{
	int		i;
	char	*dest;

	if (!ast)
		return ;
	if (ast->data.command_node.redirc)
	{
		i = 0;
		while (i < ast->data.command_node.redirc)
		{
			if (ast->data.command_node.redirection[i] == REDIR_HEREDOC)
			{
				dest = execute_heredoc(ast, i);
				ast->data.command_node.redirection[i] = REDIR_IN;
				ast->data.command_node.redir_dest[i] = dest;
				ft_lstadd_back(dest_cleanup, ft_lstnew(dest));
			}
			i++;
		}
	}
	handle_heredoc(ast->left, dest_cleanup);
	handle_heredoc(ast->right, dest_cleanup);
}
