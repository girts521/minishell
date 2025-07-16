#include "../minishell.h"

void heredoc_cleanup(t_list **dest_cleanup)
{
	t_list *current_node;

	current_node = *dest_cleanup;
	while (current_node)
	{
		unlink(current_node->content);
		free(current_node->content);
		current_node = current_node->next;
	}
}

void handle_heredoc(t_ast *ast, t_list **dest_cleanup)
{
//	int heredoc_counter;
	int i;
	char *dest;

	//heredoc_counter = 0;
	if (!ast)
		return;
	if (ast->data.command_node.redirc)
	{
		i = 0;
		while (ast->data.command_node.redirection[i])
		{
			if (ast->data.command_node.redirection[i] == REDIR_HEREDOC)
			{
				dest = execute_heredoc(ast,i);
				ast->data.command_node.redirection[i] = REDIR_IN;
				ast->data.command_node.redir_dest[i] = dest;
				//add the dest to some linked list that will be freed later
				ft_lstadd_back(dest_cleanup, ft_lstnew(dest));
			//	heredoc_counter++;
			}	
			i++;
		}
	}	
	handle_heredoc(ast->left, dest_cleanup);
	handle_heredoc(ast->right, dest_cleanup);
}

char  *execute_heredoc(t_ast *node, long redirc)
{
	char *delimiter;
	char *line;
	int temp_file;
	char *dest;

	mode_t mode = 0644;
	dest = ft_strjoin("/tmp/minishell_heredoc_", ft_itoa(redirc));
	temp_file = open(dest, O_WRONLY | O_RDONLY | O_APPEND | O_CREAT, mode);
	delimiter = node->data.command_node.redir_dest[redirc];
	line = get_next_line(0);
	while (ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
	{
		write(temp_file, line, ft_strlen(line));		
		line = get_next_line(0);
	}
	close(temp_file);
	return (dest);
}
