#include "minishell.h"

// TODO:
// Handle Quotes: Strip the outer single (') and double (") quotes from token values before saving them to the AST.
// Implement Syntax Error Handling:
// Detect and report errors for missing redirection targets (e.g., ls > | wc).
// Detect and report errors for unexpected operators at the start of a command or repeated operators (e.g., | ls).
// Refine Parser Logic:
// Improve the argument counting and storage to more cleanly separate the main command from its arguments.
// Ensure inputs with only redirections (e.g., > outfile) are parsed correctly without crashing.
//

int main (void)
{
	t_ast *current_node;
	t_ast *root;
	t_ast *pipe_node;

	current_node = create_ast_node();
	root = current_node;
    t_token *tokens1 = get_test_input_10_tokens();
	while (tokens1)
	{
		printf("%s", tokens1->value);
		if (tokens1->type >= 0 && tokens1->type <= 2)
			handle_command(tokens1, current_node);
		if (tokens1->type > 3 && tokens1->type < 8)
		{
			handle_redirect(tokens1, current_node);
			if (tokens1->next)
				tokens1 = tokens1->next;
		}
		if (tokens1->type == TOKEN_PIPE)
		{
			pipe_node = create_ast_node();
			pipe_node->type = PIPE_NODE;
			pipe_node->data.pipe_node.type = PIPE_NODE;
			pipe_node->left = root;
			root = pipe_node;
			pipe_node->right = create_ast_node();
			current_node = pipe_node->right;
		}
		tokens1 = tokens1->next;
	}
	printf("\n");
	print_ast(root);
    free_token_list(tokens1); // Clean up
	return 1;
}
