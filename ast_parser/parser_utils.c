/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gikarcev <gikarcev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:25:16 by gikarcev          #+#    #+#             */
/*   Updated: 2025/08/22 17:25:18 by gikarcev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

void	*safe_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		ft_putstr_fd("Error: Memory allocation failed!\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	clean_exit(t_token *token, t_ast *root, char *error)
{
	printf("%s\n", error);
	cleanup(root, NULL, token);
	exit(1);
}
