/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:13:00 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/19 16:25:21 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenizer/token.h"
# include "libft/libft.h"
# include "enviroment/enviroment.h"
# include "built-in/builtins.h"

void	ft_print_token_list(t_token *token);
void	ft_print_env_list(t_env *env);

#endif
