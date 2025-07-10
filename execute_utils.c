#include "libft/basic/basic.h"
#include "minishell.h"

void	execute_next_node(t_ast *root, t_env *env, char *direction)
{
	t_ast	*next_node;

	if (ft_strcmp(direction, "right") == 0)
		next_node = root->right;
	else
		next_node = root->left;
	if (next_node->type == PIPE_NODE)
		execute_pipe(next_node, env);
	else
		execute_simple_command(next_node, env);
	exit(0);
}

void	handle_children(int close_fd, int dup_fd, int pipe_fd[2])
{
	close(pipe_fd[close_fd]);
	dup2(pipe_fd[dup_fd], dup_fd);
	close(pipe_fd[dup_fd]);
}

void	handle_parent(int pipe_fd[2], int left_child, \
						int right_child, int status)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_child, &status, 0);
	waitpid(right_child, &status, 0);
}
