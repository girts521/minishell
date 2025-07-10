#include "libft/basic/basic.h"
#include "libft/get_next_line/get_next_line.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	execute_simple_command(t_ast *node, t_env *env)
{
	char	**args;
	char	*command;
	int		builtins_check;

	builtins_check = 0;
	handle_redirs(node);
	args = node->data.command_node.args;
	command = ft_strjoin("/bin/", node->data.command_node.value);
	builtins_check = ft_is_builtin(args[0]);
	if (builtins_check != 0)
		ft_select_builtin(args, env, builtins_check);
	else
		execve(command, args, NULL);
	free(command);
	command = NULL;
	exit(1);
}

void	execute_pipe(t_ast *root, t_env *env)
{
	int	left_child;
	int	right_child;
	int status;
	int pipe_fd[2];

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
			execute_pipe(root->left, env);
		else
			execute_simple_command(root->left, env);
		exit(0);
	}
	right_child = fork();
	if (right_child == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		if (root->right->type == PIPE_NODE)
			execute_pipe(root->right, env);
		else
			execute_simple_command(root->right, env);
		exit(0);
	}
	if (left_child > 0 && right_child > 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(left_child, &status, 0);
		waitpid(right_child, &status, 0);
	}
}

void	execute_ast(t_ast *root, t_env *env)
{
	int		child;
	int		status;
	char	**args;
	int		builtin_code;
	int 	pipe_child;
	t_list  *dest_cleanup;

	dest_cleanup = NULL;
	if (!root)
		return ;
	handle_heredoc(root, &dest_cleanup);
	if (root->type == PIPE_NODE)
	{
		pipe_child = fork();
		if (pipe_child == 0)
		{
			execute_pipe(root, env);
			exit(0);
		}
		else if (pipe_child > 0)
			waitpid(pipe_child, &status, 0);
	}
	else if (root->type == COMMAND_NODE)
	{
		args = root->data.command_node.args;
		builtin_code = ft_is_builtin(args[0]);
		if (builtin_code == 2 || builtin_code == 4 || builtin_code == 5 || builtin_code == 7)
		{
			ft_select_builtin(args, env, builtin_code);
			return ;
		}
		child = fork();
		if (child == 0)
		{
			handle_redirs(root);
			execute_simple_command(root, env);
		}
		else if (child > 0)
			waitpid(child, &status, 0);
		else
			perror("Error forking a child!\n");
		rl_on_new_line();
	}
	heredoc_cleanup(&dest_cleanup);
}
