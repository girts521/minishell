#include "minishell.h"

void	*safe_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		// You can use a standard error message or your clean_exit function
		ft_putstr_fd("Error: Memory allocation failed!\n", 2); // Write to STDERR
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void clean_exit(char *error)
{
	//TODO
	printf("%s\n", error);
	exit(0);
}
