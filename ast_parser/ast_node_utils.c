/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:06:29 by mmagrin           #+#    #+#             */
/*   Updated: 2025/08/07 15:06:32 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

long	count_redirs(t_token *token)
{
	long	result;

	result = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type >= 4 && token->type <= 7)
			result++;
		token = token->next;
	}
	return (result);
}

void	malloc_redir(t_token *token, t_command_node *command_node)
{
	long			redirs_num;

	redirs_num = count_redirs(token);
	command_node->redirection = (t_redirection_type *)safe_calloc \
					(1, redirs_num * sizeof(t_redirection_type *));
	command_node->redir_dest = (char **)safe_calloc \
					(1, redirs_num * sizeof(char *));
}

t_token	*handle_redirect(t_token *token, t_ast *current_node)
{
	t_command_node	*command_node;

	command_node = &current_node->data.command_node;
	if (!command_node->redirc)
	{
		command_node->redirc = 0;
		malloc_redir(token, command_node);
	}
	if (token->type == TOKEN_REDIRECT_IN)
		command_node->redirection[command_node->redirc] = REDIR_IN;
	else if (token->type == TOKEN_REDIRECT_OUT)
		command_node->redirection[command_node->redirc] = REDIR_OUT;
	else if (token->type == TOKEN_APPEND)
		command_node->redirection[command_node->redirc] = REDIR_APPEND;
	else if (token->type == TOKEN_HEREDOC)
		command_node->redirection[command_node->redirc] = REDIR_HEREDOC;
	if (token->next)
	{
		command_node->redir_dest[command_node->redirc++] = token->next->value;
		return (token->next);
	}
	return (token);
}

void	handle_command(t_token *token, t_ast *current_node)
{
	t_command_node	*command_node;

	current_node->type = COMMAND_NODE;
	command_node = &current_node->data.command_node;
	command_node->type = COMMAND_NODE;
	if (command_node->value == NULL)
	{
		command_node->value = token->value;
		command_node->args = (char **)safe_calloc(count_args(token) \
											+ 1, sizeof(char *));
		command_node->argc = 0;
	}
	command_node->args[command_node->argc++] = token->value;
}

t_ast	*handle_pipe(t_ast **root, t_ast *current_node)
{
	t_ast	*pipe_node;

	pipe_node = create_ast_node();
	pipe_node->type = PIPE_NODE;
	pipe_node->data.pipe_node.type = PIPE_NODE;
	pipe_node->left = *root;
	*root = pipe_node;
	pipe_node->right = create_ast_node();
	current_node = pipe_node->right;
	return (current_node);
}
