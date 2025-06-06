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

void handle_command(t_token *token, t_ast *current_node)
{
	//TODO
	t_command_node *command_node;

	current_node->type = COMMAND_NODE;
	command_node = &current_node->data.command_node;
	command_node->type = COMMAND_NODE;
	command_node->value = token->value;
	command_node->args = NULL;
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
    printf("Generating Test Input 1 (ls -l /tmp):\n");
    t_token *tokens1 = get_test_input_1_tokens();
   	// print_token_list(tokens1);
	
	while (tokens1)
	{
		if (tokens1->type == TOKEN_WORD)
			handle_command(tokens1, current_node);
		if (tokens1->next)
		{
			current_node->left = create_ast_node();
			current_node = current_node->left;
		}
		tokens1 = tokens1->next;
	}
	while (root) {
		printf("%d\n", root->type);
		root = root->left;
	
	}

    free_token_list(tokens1); // Clean up
	return 1;
}
