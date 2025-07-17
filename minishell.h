# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include "ast_parser/ast_parser.h"
# include <readline/readline.h>
# include "built-in/builtins.h"

void execute_ast(t_ast *root, t_env *env);
char *execute_heredoc(t_ast *node, long redirc);
char  *execute_heredoc(t_ast *node, long redirc);
void handle_heredoc(t_ast *ast, t_list **dest_cleanup);
void heredoc_cleanup(t_list **dest_cleanup);
void handle_redirs(t_ast *node);
char	*ft_get_command_path(t_env *env, char *cmd);
void	ft_expand_var(t_token *token, t_env *env);
void	ft_print_env(t_env *env);