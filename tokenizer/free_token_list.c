/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:25:45 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/04 15:32:02 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		free (token->value);
		tmp = token;
		token = token->next;
		free (tmp);
	}
}
