/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:23:29 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/19 17:48:20 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	// t_token	*token_list;

	(void)argc;
	(void)argv;
	env = ft_init_env(envp);
	ft_print_env_list(env);
	ft_free_env(env);
	// (void)envp;
	// token_list = ft_new_token_node();
	// ft_populate_token_list(token_list, "ls -l| ' wc' -l");
	// ft_print_token_list(token_list);
	// ft_free_token_list(token_list);
	return (0);
}
