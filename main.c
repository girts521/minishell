#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

void clean_exit(char *error)
{
	//TODO
	printf("%s\n", error);
	exit(0);
}

long count_args(t_token *token)
{
	long result;

	result = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type >= 0 && token->type < 3)
			result++;	
		token = token->next;
	}
	return result * sizeof(char *);
}

long count_redirs(t_token *token)
{
	long result;

	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type >= 4 && token->type <= 7)
			result++;	
		token = token->next;
	}
	return (result);
}

void handle_redirect(t_token *token, t_ast *current_node)
{
	t_command_node *command_node;
	long redirs_num;

	redirs_num = 0;
	command_node = &current_node->data.command_node;
	if (!command_node->redirc)
	{
		command_node->redirc = 0;
		redirs_num = count_redirs(token);
		command_node->redirection = (t_redirection_type *)malloc(redirs_num * sizeof(t_redirection_type *));
		command_node->redir_dest = (char **)malloc(redirs_num * sizeof(char *));
	}

	if (token->type == TOKEN_REDIRECT_IN)
		command_node->redirection[command_node->redirc] = REDIR_IN;
	else if (token->type == TOKEN_REDIRECT_OUT)
		command_node->redirection[command_node->redirc] = REDIR_OUT;	
	else if (token->type == TOKEN_APPEND)
		command_node->redirection[command_node->redirc] = REDIR_APPEND;
	else if (token->type == TOKEN_HEREDOC)
		command_node->redirection[command_node->redirc] = REDIR_HEREDOC;
	if (token->next)
		command_node->redir_dest[command_node->redirc++] = token->next->value;
}


void handle_command(t_token *token, t_ast *current_node)
{
	t_command_node *command_node;

	current_node->type = COMMAND_NODE;
	command_node = &current_node->data.command_node;
	command_node->type = COMMAND_NODE;
	if (!command_node->argc)
		command_node->argc = 0;	
	if (command_node->value)
	{
		command_node->args[command_node->argc] = token->value;
		command_node->argc++;
	}
	else
	{
		command_node->value = token->value;
		command_node->args = (char **)malloc(count_args(token));
	}

}

//Creates a node with  empty values. Used COMMAND_NODE as default, should be overwritten later.
t_ast *create_ast_node(void)
{
	t_ast *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		clean_exit("Failed to allocate memory for a node!\n");
	node->type = COMMAND_NODE;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void free_ast(void)
{
	//TODO
}



int main (void)
{
	t_ast *current_node;
	t_ast *root;

	current_node = create_ast_node();
	root = current_node;
// Test Input 4: grep "error" < log.txt >> errors.log
    printf("Generating Test Input 4 grep 'error' < log.txt >> errors.log):\n");
    t_token *tokens1 = get_test_input_7_tokens();
   	// print_token_list(tokens1);
	
	while (tokens1)
	{
		if (tokens1->type >= 0 && tokens1->type <= 2)
			handle_command(tokens1, current_node);
		if (tokens1->type > 3 && tokens1->type < 8)
		{
			handle_redirect(tokens1, current_node);
			if (tokens1->next)
				tokens1 = tokens1->next;
		}
		tokens1 = tokens1->next;
	}
	while (root)
	{
		printf("%s\n", root->data.command_node.value);
		int i = 0;
		while (i < root->data.command_node.argc) {
			printf("arg: %s\n", root->data.command_node.args[i]);
			i++;
		}
		printf("redir type: %d\n redir dest: %s\n", root->data.command_node.redirection[0], root->data.command_node.redir_dest[0]);
		printf("redir type2: %d\n redir dest2: %s\n", root->data.command_node.redirection[1], root->data.command_node.redir_dest[1]);
		root = root->left;
	
	}

    free_token_list(tokens1); // Clean up
	return 1;
}
