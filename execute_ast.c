#include "libft/basic/basic.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

//check if node has any info about redirs
//if yes then open the dest file keeping fd.keep in mind the permissions needed
//use dup2 function to update the stdin or stdout based on the redir type
//close the fd of the dest file that was opened before
void	execute_simple_command(t_ast *node)
{
	char	**args;
	char	*command;

	args = node->data.command_node.args;
	command = ft_strjoin("/bin/", node->data.command_node.value);
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
