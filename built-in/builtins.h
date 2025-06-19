/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:45:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/19 18:27:47 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>

int		ft_is_builtin(char *cmd);

void	ft_echo(t_token *token);
void	ft_pwd(void);
int		ft_exit(t_token *token, t_env *env);
int		ft_cd(t_token *token, t_env *env);

#endif
