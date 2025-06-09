#include "minishell.h"

void validate_pipe(t_token *token, t_token *previous_token)
{
	if (!previous_token || previous_token->type > 2) 
		clean_exit("Syntax error! The previous  token of a pipe must be a word like token! \n");
	if (token-> next && (token->next->type == TOKEN_EOF || token->next->type == TOKEN_PIPE))
		clean_exit("Syntax error! Pipe character can not be followed by another pipe or by an EOF\n");
}

void validate_EOF(t_token *token, t_token *previous_token)
{
	if (!previous_token || previous_token->type > 2)
		clean_exit("Syntax error! The command has to end with a word like token!\n");
	if (token->next)
		clean_exit("EOF has to be the last token!\n");
}
void validate_redirection(t_token *token, t_token *previous_token)
{
	if (previous_token && (previous_token->type > 3 && previous_token->type < 8))
		clean_exit("Syntax error! A redirection can not be followed by another redirection!\n");
	if (token->next->type > 2 || token->next->type < 0)
		clean_exit("Syntax error! A redirection must be followed by a word like token!\n");
}

void validate_token(t_token *token, t_token *previous_token)
{
	if (token->type == TOKEN_PIPE)
		validate_pipe(token, previous_token);
	else if (token->type == TOKEN_EOF)
		validate_EOF(token, previous_token);
	else if (token->type > 3 && token->type < 8)
		validate_redirection(token, previous_token);
}

