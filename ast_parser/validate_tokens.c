#include "ast_parser.h"

int	validate_pipe(t_token *token, t_token *previous_token)
{
	if (!previous_token || previous_token->type > 2)
	{
		printf("Syntax error! The previous \
					token of a pipe must be a word like token! \n");
		return (1);
	}
	if (!token->next || (token->next->type == TOKEN_EOF || \
							token->next->type == TOKEN_PIPE))
	{
		printf("Syntax error! Pipe \
		character can not be followed by another pipe or by an EOF\n");
		return (1);
	}
	return (0);
}

int	validate_eof(t_token *token, t_token *previous_token)
{
	if (previous_token->type > 2)
	{
		printf("Syntax error! The command has to \
					end with a word like token!\n");
		return (1);
	}
	if (token->next)
	{
		printf("EOF has to be the last token!\n");
		return (1);
	}
	return (0);
}

int	validate_redirection(t_token *token, t_token *previous_token)
{
	if (previous_token && (previous_token->type > 3 \
		&& previous_token->type < 8))
	{
		printf("Syntax error! A redirection can not \
					be followed by another redirection!\n");
		return (1);
	}
	if (token->next->type > 2 || token->next->type < 0)
	{
		printf("Syntax error! A redirection must be \
					followed by a word like token!\n");
		return (1);
	}
	return (0);

}

int	validate_token(t_token *token, t_token *previous_token)
{
	int result;

	result = 0;
	if (token->type == TOKEN_PIPE)
		result = validate_pipe(token, previous_token);
	else if (token->type == TOKEN_EOF)
		result = validate_eof(token, previous_token);
	else if (token->type > 3 && token->type < 8)
		result = validate_redirection(token, previous_token);
	return (result);
}
