/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gikarcev <gikarcev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:25:23 by gikarcev          #+#    #+#             */
/*   Updated: 2025/08/22 17:25:24 by gikarcev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

t_ast	*parser(t_token *tokens)
{
	t_ast	*current_node;
	t_ast	*root;

	if (!tokens || tokens->type == TOKEN_EOF)
		return (NULL);
	current_node = create_ast_node();
	root = current_node;
	while (tokens)
	{
		if (tokens->type == TOKEN_EOF)
			break ;
		if (tokens->type >= 0 && tokens->type <= 2)
			handle_command(tokens, current_node);
		if (tokens->type > 3 && tokens->type < 8)
			tokens = handle_redirect(tokens, current_node);
		if (tokens->type == TOKEN_PIPE)
			current_node = handle_pipe(&root, current_node);
		tokens = tokens->next;
	}
	return (root);
}

// int	main(void)
// {
// 	t_ast	*root;
// 	t_token	*tokens1;
//
// 	tokens1 = get_test_input_11_tokens();
// 	root = parser(tokens1);
// 	print_ast(root);
// 	free_token_list(tokens1);
// 	cleanup(root);
// 	return (1);
//
/*
 */
