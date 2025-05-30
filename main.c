/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:23:06 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/29 19:11:44 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env_list(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		else if (env->key)
			printf("%s=\n", env->key);
		env = env->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env	**env;

	(void)argc;
	(void)argv;
	env = ft_init_env(envp);
	ft_print_env_list(*env);
	return (0);
}
