#include "libft/basic/basic.h"
#include "minishell.h"
#include <readline/readline.h>

void execute_ast(t_ast *root)
{
	int child;
	char **args;
	char *command;

	child = fork();
	if (child == 0)
	{
		// command = (char *)malloc((ft_strlen("/bin/") + ft_strlen(root->data.command_node.value)) * sizeof(char) );
		args = root->data.command_node.args;
		command = ft_strjoin("/bin/", root->data.command_node.value);	
		execve(command, args, NULL);
		free(command);
		command = NULL;
		exit(1);
	}
	wait(&child);
	rl_on_new_line();

}

