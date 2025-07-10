#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/history.h>
//
// int	main(int argc, char **argv, char **envp)
// {
// 	t_ast	*root;
// 	t_token	*tokens;
// 	t_env	*env;
// 	char	*input;
//
// 	(void)argc;
// 	(void)**argv;
// 	env = ft_init_env(envp);
// 	while (1)
// 	{
// 		input = readline("$> ");
// 		if (input == NULL)
// 		{
// 			printf("EOF...Quiting!");
// 			break ;
// 		}
// 		if (ft_strcmp(input, "exit") == 0)
// 			break ;
// 		add_history(input);
// 		tokens = ft_new_token_node();
// 		ft_populate_token_list(tokens, input);
// 		root = parser(tokens);
// 		// print_ast(root);
// 		execute_ast(root, env);
// 		free(input);
// 		ft_free_token_list(tokens);
// 		cleanup(root);
// 		rl_on_new_line();
// 	}
// 	ft_free_env(env);
// 	rl_clear_history();
// 	return (1);
// }

int	main(int argc, char **argv, char **envp)
{
	t_ast	*root;
	t_token	*tokens;
	t_env	*env;
	
	// We are going to simulate a single command line entry.
	char *test_input = ft_strdup("echo hello | ls -la | wc -l");

	(void)argc;
	(void)argv;
	
	printf("--- RUNNING SINGLE-SHOT PARSER TEST ---\n");

	// 1. Initialize environment (as before)
	env = ft_init_env(envp);

	// 2. Tokenize the hardcoded input
	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, test_input);

	// 3. Parse the tokens into an AST
	root = parser(tokens);
	
	// We don't need to execute the command for this test.
	// We only care about allocation and cleanup.
	execute_ast(root, env);

	// 4. Perform the cleanup, exactly as you do in your loop
	cleanup(root);
	ft_free_token_list(tokens);
	ft_free_env(env);
	free(test_input); // Free the hardcoded string

	printf("--- TEST COMPLETE ---\n");

	// 5. Exit immediately. No rl_clear_history() is needed as readline was not used.
	return (0);
}
