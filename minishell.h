#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

// Your provided token type definition
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_STRING,
	TOKEN_SQUOTE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}			t_token_type;

typedef enum e_ast_node_type
{
	COMMAND_NODE,
	PIPE_NODE
}				t_ast_node_type;

typedef enum e_redirection_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}				t_redirection_type;

typedef struct s_pipe_node
{
	t_ast_node_type	type;
	// TODO;
}				t_pipe_node;

typedef struct s_command_node
{
	t_ast_node_type		type;
	char				*value;
	char				**args;
	long				argc;
	long				redirc;
	t_redirection_type	*redirection;
	char				**redir_dest;

}				t_command_node;

typedef union u_ast_node
{
	t_command_node	command_node;
	t_pipe_node		pipe_node;
}				t_ast_node;

typedef struct s_ast
{
	t_ast_node_type	type;	
	struct s_ast	*left;
	struct s_ast	*right;
	t_ast_node		data;
}				t_ast;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

t_ast	*create_ast_node(void);
void	free_token_list(t_token *token_list);
void	print_token_list(t_token *token_list);
void	free_ast(void);
long	count_args(t_token *token);
long	count_redirs(t_token *token);
t_token	*handle_redirect(t_token *token, t_ast *current_node);
void	handle_command(t_token *token, t_ast *current_node);
void	*safe_calloc(size_t count, size_t size);
void	clean_exit(t_token *token, t_ast *root, char *error);
void	cleanup(t_ast *root);
t_ast	*handle_pipe(t_ast **root, t_ast *current_node);
void	validate_token(t_token *token, t_token *previous_token, \
					t_ast *root, t_token *token_head);
long	count_args(t_token *token);
t_ast	*parser(t_token *tokens);
t_token	*get_test_input_1_tokens(void);
t_token	*get_test_input_2_tokens(void);
t_token	*get_test_input_3_tokens(void);
t_token	*get_test_input_4_tokens(void);
t_token	*get_test_input_5_tokens(void);
t_token	*get_test_input_6_tokens(void);
t_token	*get_test_input_7_tokens(void);
t_token	*get_test_input_8_tokens(void);
t_token	*get_test_input_9_tokens(void);
t_token	*get_test_input_10_tokens(void);
t_token	*get_test_input_11_tokens(void);
t_token	*get_test_input_12_tokens(void);
t_token	*get_test_input_13_tokens(void);
t_token	*get_test_input_14_tokens(void);
void	print_ast(t_ast *root);
