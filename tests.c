#include "minishell.h"

int	tests(int argc, char **argv, char **envp)
{
	t_ast	*root;
	t_token	*tokens;
	t_env	*env;
	char *test_input; 

	test_input = ft_strdup("echo hello | ls -la | wc -l");
	(void)argc;
	(void)argv;
	printf("--- RUNNING echo hello | ls -la | wc -l test ---\n");
	env = ft_init_env(envp);
	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, test_input);
	root = parser(tokens);
	execute_ast(root, env);
	cleanup(root);
	ft_free_token_list(tokens);
	ft_free_env(env);
	free(test_input);
	printf("--- TEST COMPLETE ---\n");

	printf("\n");

	test_input = ft_strdup("ls -la | wc -l");
	printf("--- RUNNING ls -la | wc -l ---\n");
	env = ft_init_env(envp);
	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, test_input);
	root = parser(tokens);
	execute_ast(root, env);
	cleanup(root);
	ft_free_token_list(tokens);
	ft_free_env(env);
	free(test_input);
	printf("--- TEST COMPLETE ---\n");

	printf("\n");

	test_input = ft_strdup("export test");
	printf("--- RUNNING export test ---\n");
	env = ft_init_env(envp);
	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, test_input);
	root = parser(tokens);
	execute_ast(root, env);
	cleanup(root);
	ft_free_token_list(tokens);
	printf("--- TEST COMPLETE ---\n");
	
	printf("\n");

	test_input = ft_strdup("export | grep --context 5 test");
	printf("--- RUNNING export | grep test ---\n");
	env = ft_init_env(envp);
	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, test_input);
	root = parser(tokens);
	execute_ast(root, env);
	cleanup(root);
	ft_free_token_list(tokens);
	printf("--- TEST COMPLETE ---\n");

	printf("\n");

	test_input = ft_strdup("cd ./libft ");
	printf("--- RUNNING cd libft ---\n");
	env = ft_init_env(envp);
	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, test_input);
	root = parser(tokens);
	execute_ast(root, env);
	cleanup(root);
	ft_free_token_list(tokens);
	ft_free_env(env);
	free(test_input);
	printf("--- TEST COMPLETE ---\n");

	printf("\n");

	test_input = ft_strdup("pwd");
	printf("--- RUNNING pwd---\n");
	env = ft_init_env(envp);
	tokens = ft_new_token_node();
	ft_populate_token_list(tokens, test_input);
	root = parser(tokens);
	execute_ast(root, env);
	cleanup(root);
	ft_free_token_list(tokens);
	ft_free_env(env);
	free(test_input);
	printf("--- TEST COMPLETE ---\n");

	printf("\n");

	return (0);
}
