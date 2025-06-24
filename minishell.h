# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include "ast_parser/ast_parser.h"
# include <readline/readline.h>
# include "built-in/builtins.h"

void execute_ast(t_ast *root);
