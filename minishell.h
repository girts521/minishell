#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "ast_parser/ast_parser.h"
#include <readline/readline.h>
#include "built-in/builtins.h"

int	tests(int argc, char **argv, char **envp);

void	execute_ast(t_ast *root, t_env *env);
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
