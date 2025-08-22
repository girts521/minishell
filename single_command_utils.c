/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gikarcev <gikarcev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:03:15 by gikarcev          #+#    #+#             */
/*   Updated: 2025/08/22 18:03:18 by gikarcev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_in_single_command(t_ast *root, t_shell *shell)
{
	if (handle_redirs(root) == 1)
	{
		shell->last_exit_code = 1;
		exit(1);
	}
	if (root->data.command_node.value)
		execute_simple_command(root, shell);
	else 
		exit(0);
}

void	handle_parent_in_single_command(int child, int *status, t_shell *shell)
{
	waitpid(child, status, 0);
	if (WIFEXITED(*status))
		shell->last_exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		shell->last_exit_code = 128 + WTERMSIG(*status);
}
