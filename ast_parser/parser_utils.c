#include "ast_parser.h"

void	*safe_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		ft_putstr_fd("Error: Memory allocation failed!\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	clean_exit(t_token *token, t_ast *root, char *error)
{
	printf("%s\n", error);
	cleanup(root, NULL, token);
	exit(1);
}
