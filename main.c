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
	while (token->type == TOKEN_WORD)
	{
		result++;
		token = token->next;
	}
	return result * sizeof(char *);
}

void handle_redirect(t_token *token, t_ast *current_node)
{
	
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
		printf("here %d\n", command_node->argc);
		command_node->args[command_node->argc] = token->value;
		command_node->argc++;
	}
	else
	{
		command_node->value = token->value;
		command_node->args = (char **)malloc(count_args(token));
	}
	command_node->redirection = REDIR_NONE;


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
    printf("Generating Test Input 1 (ls -l /tmp >):\n");
    t_token *tokens1 = get_test_input_1_tokens();
   	// print_token_list(tokens1);
	
	while (tokens1)
	{
		if (tokens1->type == TOKEN_WORD)
			handle_command(tokens1, current_node);
		if (tokens1->type > 3 && tokens1->type < 7)
			handle_redirect(tokens1, current_node);
		tokens1 = tokens1->next;
	}
	while (root) {
		printf("%s\n", root->data.command_node.value);
		int i = 0;
		while (i < root->data.command_node.argc) {
			printf("arg: %s\n", root->data.command_node.args[i]);
			i++;
		
		}
		root = root->left;
	
	}

    free_token_list(tokens1); // Clean up
	return 1;
}
