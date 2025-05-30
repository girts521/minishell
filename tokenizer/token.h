/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:11:26 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/30 18:43:43 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type {
	TOKEN_WORD,			// Regular word (command or arg)
	TOKEN_DQUOTE,		// Double quoted string (defer $ expansion)
	TOKEN_SQUOTE,		// Single quoted string (no $ expansion)
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_IN,	// <
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_EOF			// End marker (optional)
} t_token_type;

typedef struct s_token {
	t_token_type	type ;	// Type of token
	char			*value;	// Raw string (e.g., "echo", ">", "hello $USER")
	struct s_token	*next;	// Next token in the list
} t_token;

/*tokenizer.c*/

/*token_utils.c*/
int	ft_recogn_t(char *line);
int	ft_nr_token(char *line);

#endif
