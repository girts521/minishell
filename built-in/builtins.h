/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:45:14 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/23 17:50:31 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>

typedef struct s_shell	t_shell;
typedef struct s_env		t_env;

int		ft_is_builtin(char *cmd);
void	ft_select_builtin(char **args, t_shell *shell, int builtins_check);

/*built-ins*/
int		ft_cd(char **args, t_env *env);
void	ft_echo(char **args);
int		ft_env(char **args, t_env *env);
int		ft_exit(char **args, t_shell *shell);
int		ft_export(char **args, t_env *env);
void	ft_pwd(void);
int		ft_unset(char **args, t_env **env);

/*usefull*/
char	**ft_env_to_envp(t_env *env);
int		ft_controll_token(char *args);
int		ft_envlst_size(t_env *env);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

#endif
