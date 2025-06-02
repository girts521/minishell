#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Your provided token type definition
typedef enum e_token_type {
    TOKEN_WORD,         // 0 Regular word (command or arg)
    TOKEN_STRING,       // 1 Double quoted string (defer $ expansion)
    TOKEN_SQUOTE,       // 2 Single quoted string (no $ expansion)
    TOKEN_PIPE,         // 3 |
    TOKEN_REDIRECT_IN,  // 4 <
    TOKEN_REDIRECT_OUT, // 5 >
    TOKEN_APPEND,       // 6 >>
    TOKEN_HEREDOC,      // 7 <<
    TOKEN_EOF           // 8 End marker (optional)
} t_token_type;

typedef enum e_ast_node_type
{
	COMMAND_NODE,
	PIPE_NODE
} t_ast_node_type;

typedef enum e_redirection_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
} t_redirection_type;

typedef struct	s_pipe_node 
{
	e_ast_node_type type;
	// TODO;

} t_pipe_node;

typedef struct s_command_node
{
	e_ast_node_type type;
	char *value;
	char **args;
	t_redirection_type redirection;

} t_command_node;

typedef union u_ast_node
{
	t_command_node command_node;
	t_pipe_node pipe_node;
} t_ast_node;

typedef struct s_ast
{
	e_ast_node_type type;	
	t_ast_node *left;
	t_ast_node *right;

	t_ast_node data;
 } t_ast;


// Your provided token structure definition
typedef struct s_token {
    t_token_type type;    // Type of token
    char *value;          // Raw string (e.g., "echo", ">", "hello $USER")
    struct s_token *next;   // Next token in the list
} t_token;

void free_token_list(t_token *token_list);
void print_token_list(t_token *token_list);
void print_token_list(t_token *token_list); 
t_token *get_test_input_1_tokens();
t_token *get_test_input_2_tokens();
