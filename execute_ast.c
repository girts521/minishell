#include "libft/basic/basic.h"
#include "libft/get_next_line/get_next_line.h"
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

// get next line on stdin 
// check if the line is == to delimiter
// if yes then 
//
//
// // Refined Step-by-Step Plan
// Here is a slightly more detailed version of your plan, confirming your logic:
//
// Start "Heredoc Pass": Before any execution, begin a complete traversal of the Abstract Syntax Tree (AST).
//
// Find & Execute Heredocs: When a REDIR_HEREDOC node is found:
//
// Prompt the user and read input until the delimiter is found.
//
// Write this input to a new temporary file (e.g., /tmp/minishell_heredoc_123).
//
// Add the path of this temporary file to a dedicated cleanup list.
//
// Transform the AST Node:
//
// Change the node's redirection type from REDIR_HEREDOC to REDIR_IN.
//
// Update the node's redirection destination to be the path of the temporary file you just created.
//
// Finish Pass 1: Continue traversing until the entire tree has been checked.
//
// Start "Execution Pass": Begin the main execution of the now-modified AST.
//
// Execute commands and pipelines as you normally would. When your handle_redirs function sees the node you changed, it will treat it as a simple input redirection from a file, which your handle_redir_in function already knows how to do.
//
// Wait & Clean Up: After the entire command
//has finished executing (e.g., after waitpid in your main loop), iterate through your cleanup list and unlink() every temporary file path it contains.
//
//##########################################
// traverse the tree
//
// if a heredoc is encountered -> execute it
//
// add the temp file path to an array or linked list
//
// update the command nodes execution from heredoc to redirin
//
// move till the end of tree
//
// go to main execution loop
//
// execute all nodes as usual
// //##########################################

char *execute_heredoc(t_ast *node, long redirc);

void handle_heredoc(t_ast *ast)
{
	int heredoc_counter;
	int i;
	char *dest;

	heredoc_counter = 0;
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
				heredoc_counter++;
			}	
			i++;
		}
	}	
	handle_heredoc(ast->left);
	handle_heredoc(ast->right);
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
	temp_file = open(dest, O_RDONLY);
	dup2(temp_file, STDIN_FILENO);
	close(temp_file);
	return (dest);
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
	handle_heredoc(root);
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
