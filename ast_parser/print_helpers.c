// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:23:06 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/12 16:30:02 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

void	ft_print_env_list(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			ft_printf("%s=%s\n", env->key, env->value);
		else if (env->key)
			ft_printf("%s=\n", env->key);
		env = env->next;
	}
}

#include <stdio.h>

void	ft_print_token_list(t_token *token)
{
	while (token)
	{
		ft_printf("Type: %d Value: %s\n", token->type, token->value);
		token = token->next;
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;
// 	t_token	*token_list;
//
// 	(void)argc;
// 	(void)argv;
// 	env = ft_init_env(envp);
// 	ft_print_env_list(env);
// 	ft_free_env(env);
// 	// (void)envp;
// 	token_list = ft_new_token_node();
// 	ft_populate_token_list(token_list, "ls -l|wc -l");
// 	ft_print_token_list(token_list);
// 	ft_free_token_list(token_list);
// 	return (0);
// }
