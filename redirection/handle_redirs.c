#include "../minishell.h"

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
