#include "enviroment/enviroment.h"
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
	char	**envp;
	char	*command;
	int		builtins_check;

	builtins_check = 0;
	handle_redirs(node);
	args = node->data.command_node.args;
	builtins_check = ft_is_builtin(args[0]);
	if (builtins_check != 0)
		ft_select_builtin(args, env, builtins_check);
	else
	{
		command = ft_get_command_path(env, node->data.command_node.value);
		if (!command)
			exit(127);
		envp = ft_env_to_envp(env);
		execve(command, args, envp);
		ft_free_pointertopointer(envp);
		free(command);
	}
	command = NULL;
	exit(0);
}

void	execute_pipe(t_ast *root, t_env *env)
{
	int	left_child;
	int	right_child;
	int	status;
	int	pipe_fd[2];

	status = 1;
	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating pipe!\n");
		exit(1);
	}
	left_child = fork();
	if (left_child == 0)
	{
		handle_children(0, 1, pipe_fd);
		execute_next_node(root, env, "left");
	}
	right_child = fork();
	if (right_child == 0)
	{
		handle_children(1, 0, pipe_fd);
		execute_next_node(root, env, "right");
	}
	if (left_child > 0 && right_child > 0)
		handle_parent(pipe_fd, left_child, right_child, status);
}

void	execute_single_command(t_ast *root, t_env *env, int *status)
{
	char	**args;
	int		builtin_code;
	int		child;

	args = root->data.command_node.args;
	builtin_code = ft_is_builtin(args[0]);
	if (builtin_code == 2 || builtin_code == 4 || \
			builtin_code == 5 || builtin_code == 7)
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
		waitpid(child, status, 0);
	else
		perror("Error forking a child!\n");
	rl_on_new_line();
}

void	prepare_pipe(struct sigaction *sa_quit, \
					int *status, t_ast *root, t_env *env)
{
	int	pipe_child;

	sa_quit->sa_handler = quit_handler;
	sigaction(SIGQUIT, sa_quit, NULL);
	pipe_child = fork();
	if (pipe_child == 0)
	{
		execute_pipe(root, env);
		exit(0);
	}
	else if (pipe_child > 0)
		waitpid(pipe_child, status, 0);
}

void	execute_ast(t_ast *root, t_env *env, struct sigaction *sa_quit)
{
	int		status;
	t_list	*dest_cleanup;

	dest_cleanup = NULL;
	if (!root)
		return ;
	handle_heredoc(root, &dest_cleanup);
	if (root->type == PIPE_NODE)
		prepare_pipe(sa_quit, &status, root, env);
	else if (root->type == COMMAND_NODE)
	{
		signal_switch(HANDLE, sa_quit);
		execute_single_command(root, env, &status);
		signal_switch(IGNORE, sa_quit);
	}
	heredoc_cleanup(&dest_cleanup);
}
