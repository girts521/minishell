#include "../minishell.h"

void	handle_redir_append(t_ast *node, long redirc)
{
	char	*dest;	
	int		dest_fd;

	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (dest_fd < 0)
	{
		perror(dest);
		//handle clean exit
	}
	dup2(dest_fd, STDOUT_FILENO);
	close(dest_fd);
}

void	handle_redir_out(t_ast *node, long redirc)
{
	char	*dest;	
	int		dest_fd;

	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (dest_fd < 0)
	{
		perror(dest);
		//handle clean exit
	}
	dup2(dest_fd, STDOUT_FILENO);
	close(dest_fd);
}

void	handle_redir_in(t_ast *node, long redirc)
{
	char	*dest;	
	int		dest_fd;

	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_RDONLY);
	if (dest_fd < 0)
	{
		perror(dest);
		//handle clean exit
	}
	dup2(dest_fd, STDIN_FILENO);
	close(dest_fd);
}

void	handle_redirs(t_ast *node)
{
	t_redirection_type	redir_type;
	long				redirc;

	redirc = 0;
	if (node->data.command_node.redirc == 0)
		return ;
	redir_type = node->data.command_node.redirection[redirc];
	while (redir_type)
	{
		if (redir_type == REDIR_IN)
			handle_redir_in(node, redirc);
		else if (redir_type == REDIR_OUT)
			handle_redir_out(node, redirc);
		else if (redir_type == REDIR_APPEND)
			handle_redir_append(node, redirc);
		redirc++;
		redir_type = node->data.command_node.redirection[redirc];
	}
}
