#include "libft/basic/basic.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

//check if node has any info about redirs
//if yes then open the dest file keeping fd.keep in mind the permissions needed
//use dup2 function to update the stdin or stdout based on the redir type
//close the fd of the dest file that was opened before

void handle_heredoc(t_ast *node, long redirc)
{
	char *delimiter;

	delimiter = node->data.command_node.redir_dest[redirc];

}

void handle_redir_append(t_ast *node, long redirc)
{
	char *dest;	
	int dest_fd;

	mode_t mode = 0644;
	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_WRONLY | O_APPEND | O_CREAT, mode);
	if (dest_fd < 0)
	{
		perror(dest);
		//handle clean exit
	}
	dup2(dest_fd, STDOUT_FILENO);
	close(dest_fd);


}

void handle_redir_out(t_ast *node, long redirc)
{
	char *dest;	
	int dest_fd;

	mode_t mode = 0644;
	dest = node->data.command_node.redir_dest[redirc];
	dest_fd = open(dest, O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (dest_fd < 0)
	{
		perror(dest);
		//handle clean exit
	}
	dup2(dest_fd, STDOUT_FILENO);
	close(dest_fd);

}

void handle_redir_in(t_ast *node, long redirc)
{
	char *dest;	
	int dest_fd;

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

void handle_redirs(t_ast *node)
{
	t_redirection_type redir_type;
	long redirc;

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
		// else if (redir_type == REDIR_HEREDOC)
		// 	handle_heredoc(node, redirc);
		else if (redir_type == REDIR_APPEND)
			handle_redir_append(node, redirc);
		redirc++;
		redir_type = node->data.command_node.redirection[redirc];
	}	
}

void	execute_simple_command(t_ast *node)
{
	char	**args;
	char	*command;

	args = node->data.command_node.args;
	command = ft_strjoin("/bin/", node->data.command_node.value);
	printf("redirc: %ld\n", node->data.command_node.redirc);
	handle_redirs(node);
	execve(command, args, NULL);
	free(command);
	command = NULL;
	exit(1);
}

void	execute_pipe(int pipe_fd[2], t_ast *root)
{
	int	left_child;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating pipe!\n");
		exit(1);
	}
	left_child = fork();
	if (left_child == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		if (root->left->type == PIPE_NODE)
			execute_ast(root->left);
		else
			execute_simple_command(root->left);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	if (root->right->type == PIPE_NODE)
		execute_ast(root->right);
	else
		execute_simple_command(root->right);
}

void	execute_ast(t_ast *root)
{
	int	child;
	int	status;
	int	pipe_fd[2];

	if (!root)
		return ;
	if (root->type == PIPE_NODE)
		execute_pipe(pipe_fd, root);
	else if (root->type == COMMAND_NODE)
	{
		child = fork();
		if (child == 0)
			execute_simple_command(root);
		else if (child > 0)
			waitpid(child, &status, 0);
		else
			perror("Error forking a child!\n");
		rl_on_new_line();
	}
}
