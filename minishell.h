/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:31:56 by mattiamagri       #+#    #+#             */
/*   Updated: 2025/08/07 14:37:02 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast_parser/ast_parser.h"
# include "built-in/builtins.h"
# include "enviroment/enviroment.h"
# include "libft/libft.h"
# include "tokenizer/token.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>

extern volatile sig_atomic_t	g_signal_number;

typedef enum e_sigquit
{
	IGNORE,
	HANDLE
}			t_sigquit;

typedef struct s_shell
{
	t_env	*env;
	long	last_exit_code;
}	t_shell;

int		tests(int argc, char **argv, char **envp);

void	execute_next_node(t_ast *root, t_shell *shell, char *direction);

void	execute_simple_command(t_ast *node, t_shell *shell);
void	execute_pipe(t_ast *root, t_shell *shell);
void	execute_ast(t_ast *root, t_shell *shell, struct sigaction *sa_quit);
void	handle_children(int close_fd, int dup_fd, int pipe_fd[2]);
void	handle_parent(int pipe_fd[2], int left_child, \
						int right_child, int status);

char	*execute_heredoc(t_ast *node, long redirc);
char	*execute_heredoc(t_ast *node, long redirc);
void	handle_heredoc(t_ast *ast, t_list **dest_cleanup);
void	heredoc_cleanup(t_list **dest_cleanup);
void	handle_redirs(t_ast *node);

void	handle_execution_sigint(int sig);
void	handle_interactive_sigint(int sig);
void	quit_handler(int sig);
void	signal_switch(t_sigquit status, struct sigaction *sa_quit);
void	handle_sigint(int sig);
void	prepare_signals(struct sigaction *sa_int, struct sigaction *sa_quit);

char	*ft_get_commandpath(t_env *env, char *cmd);

void	ft_expand_var(t_token *token, t_shell *shell);
void	ft_print_env(t_env *env);
int		ft_is_valid_env_char(int c);
int		ft_exceve_use(t_shell *shell, char **args, char *command_node_value);

#endif
