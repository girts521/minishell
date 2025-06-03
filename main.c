#include "libft.h"
#include <cstdlib>
#include <stdio.h>
#include "minishell.h"

void clean_exit(char *error)
{
	//TODO
}

void handle_command(t_token *token, t_ast *ast)
{
	//TODO
			
}

t_ast *create_ast_node(t_ast_node_type type)
{
	//TODO
	t_ast *node;

	node = (t_ast)malloc(sizeof(t_ast_node));
	if (!node)
		clean_exit("Failed to allocate memore for a node!\n");
	return (node);
}

void free_ast(void)
{
	//TODO
}



int main (void)
{
	t_ast *ast;

	ast = create_ast_node();
    printf("Generating Test Input 1 (ls -l /tmp):\n");
    t_token *tokens1 = get_test_input_1_tokens();
   	// print_token_list(tokens1);
	
	while (tokens1)
	{
		if (tokens1->type == TOKEN_WORD)
		{
			handle_command(tokens1, ast);	
		}	
	}

    free_token_list(tokens1); // Clean up
	return 1;
}
