#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

void heredoc_cleanup(t_list **dest_cleanup)
{
	t_list *current_node;
	t_list *next_node;

	current_node = *dest_cleanup;
	next_node = NULL;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		unlink((char *)current_node->content);
		free((char *)current_node->content);
		free(current_node);
		current_node = next_node;
	}
}

char  *execute_heredoc(t_ast *node, long redirc)
{
	char *delimiter;
	char *line;
	int temp_file;
	char *dest;
	int delimiter_len;

	mode_t mode = 0644;
	dest = ft_strjoin("/tmp/minishell_heredoc_", ft_itoa(redirc));
	temp_file = open(dest, O_WRONLY | O_RDONLY | O_APPEND | O_CREAT, mode);
	delimiter_len = 0;
	if (temp_file == -1)
	{
		free(dest);
		perror("Failed to open a temp file");
		return (NULL);
	}
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
		if (ft_strlen(line) == delimiter_len + 1 && ft_strncmp(line, delimiter, delimiter_len) == 0)
        {
            free(line);
            break;
        }
		write(temp_file, line, ft_strlen(line));		
		free(line);
	}
	close(temp_file);
	return (dest);
}

void handle_heredoc(t_ast *ast, t_list **dest_cleanup)
{
	int heredoc_counter;
	int i;
	char *dest;

	heredoc_counter = 0;
	if (!ast)
		return ;
	if (ast->data.command_node.redirc)
	{
		i = 0;
		while (i < ast->data.command_node.redirc)
		{
			if (ast->data.command_node.redirection[i] == REDIR_HEREDOC)
			{
				dest = execute_heredoc(ast,i);
				ast->data.command_node.redirection[i] = REDIR_IN;
				ast->data.command_node.redir_dest[i] = dest;
				ft_lstadd_back(dest_cleanup, ft_lstnew(dest));
				heredoc_counter++;
			}	
			i++;
		}
	}	
	handle_heredoc(ast->left, dest_cleanup);
	handle_heredoc(ast->right, dest_cleanup);
}

