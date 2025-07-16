#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "ast_parser/ast_parser.h"
#include <readline/readline.h>
#include "built-in/builtins.h"
extern volatile sig_atomic_t	g_signal_number;

typedef enum e_sigquit
{
	IGNORE,
	HANDLE
}			t_sigquit;

int		tests(int argc, char **argv, char **envp);
void	execute_ast(t_ast *root, t_env *env, struct sigaction *sa_quit);
char	*execute_heredoc(t_ast *node, long redirc);
char	*execute_heredoc(t_ast *node, long redirc);
void	handle_heredoc(t_ast *ast, t_list **dest_cleanup);
void	heredoc_cleanup(t_list **dest_cleanup);
void	handle_redirs(t_ast *node);
void	execute_pipe(t_ast *root, t_env *env);
void	execute_simple_command(t_ast *node, t_env *env);
void	execute_next_node(t_ast *root, t_env *env, char *direction);
void	handle_children(int close_fd, int dup_fd, int pipe_fd[2]);
void	handle_parent(int pipe_fd[2], int left_child, \
						int right_child, int status);
void	handle_execution_sigint(int sig);
void	handle_interactive_sigint(int sig);
void	quit_handler(int sig);
void	signal_switch(t_sigquit status, struct sigaction *sa_quit);
void	handle_sigint(int sig);
void	prepare_signals(struct sigaction *sa_int, struct sigaction *sa_quit);
char	*ft_get_command_path(t_env *env, char *cmd);
void	ft_expand_var(t_token *token, t_env *env);
void	ft_print_env(t_env *env);
