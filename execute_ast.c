/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:25:21 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/07 14:54:59 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_command(t_ast *node, t_shell *shell)
{
	char	**args;
	int		builtins_check;

	builtins_check = 0;
	handle_redirs(node);
	args = node->data.command_node.args;
	builtins_check = ft_is_builtin(args[0]);
	if (builtins_check != 0)
		ft_select_builtin(args, shell, builtins_check);
	else
		exit(ft_exceve_use(shell, args, node->data.command_node.value));
	exit(shell->last_exit_code);
}

void	execute_pipe(t_ast *root, t_shell *shell)
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
		execute_next_node(root, shell, "left");
	}
	right_child = fork();
	if (right_child == 0)
	{
		handle_children(1, 0, pipe_fd);
		execute_next_node(root, shell, "right");
	}
	if (left_child > 0 && right_child > 0)
		handle_parent(pipe_fd, left_child, right_child, status);
}

void	execute_single_command(t_ast *root, t_shell *shell, int *status)
{
	char	**args;
	int		builtin_code;
	int		child;

	args = root->data.command_node.args;
	builtin_code = ft_is_builtin(args[0]);
	if (builtin_code == 2 || builtin_code == 4 || \
			builtin_code == 5 || builtin_code == 7)
	{
		ft_select_builtin(args, shell, builtin_code);
		return ;
	}
	child = fork();
	if (child == 0)
	{
		handle_redirs(root);
		execute_simple_command(root, shell);
	}
	else if (child > 0)
		waitpid(child, status, 0);
	else
		perror("Error forking a child!\n");
	rl_on_new_line();
}

void	prepare_pipe(struct sigaction *sa_quit, \
					int *status, t_ast *root, t_shell *shell)
{
	int	pipe_child;

	sa_quit->sa_handler = quit_handler;
	sigaction(SIGQUIT, sa_quit, NULL);
	pipe_child = fork();
	if (pipe_child == 0)
	{
		execute_pipe(root, shell);
		exit(0);
	}
	else if (pipe_child > 0)
		waitpid(pipe_child, status, 0);
}

void	execute_ast(t_ast *root, t_shell *shell, struct sigaction *sa_quit)
{
	int		status;
	t_list	*dest_cleanup;

	dest_cleanup = NULL;
	if (!root)
		return ;
	handle_heredoc(root, &dest_cleanup);
	if (root->type == PIPE_NODE)
		prepare_pipe(sa_quit, &status, root, shell);
	else if (root->type == COMMAND_NODE)
	{
		signal_switch(HANDLE, sa_quit);
		execute_single_command(root, shell, &status);
		signal_switch(IGNORE, sa_quit);
	}
	heredoc_cleanup(&dest_cleanup);
}
