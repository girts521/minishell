/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:33:13 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/07 16:51:06 by mattiamagri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*ft_init_env(char *envp[]);
t_env	*ft_create_node(void *content);
void	ft_env_add_back(t_env **env, t_env *new);
char	*ft_extract_value_env(char *env_str);
char	*ft_extract_key_env(char *env_str);
int		ft_strch_i(char *str, char c);
void	ft_free_env(t_env *env);

#endif
