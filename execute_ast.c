#include "libft/basic/basic.h"
#include "minishell.h"
#include <readline/readline.h>

void execute_ast(t_ast *root)
{
	int child;
	char **args;
	char *command;
	int status;

	child = fork();
	if (child == 0)
	{
		args = root->data.command_node.args;
		command = ft_strjoin("/bin/", root->data.command_node.value);	
		execve(command, args, NULL);
		free(command);
		command = NULL;
		exit(1);
	}
	waitpid(child, &status, 0);
	rl_on_new_line();
}

