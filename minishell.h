# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include "ast_parser/ast_parser.h"
# include <readline/readline.h>

void execute_ast(t_ast *root);
char *execute_heredoc(t_ast *node, long redirc);
char  *execute_heredoc(t_ast *node, long redirc);
void handle_heredoc(t_ast *ast, t_list **dest_cleanup);
void heredoc_cleanup(t_list **dest_cleanup);
void handle_redirs(t_ast *node);
