/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:11:26 by mmagrin           #+#    #+#             */
/*   Updated: 2025/06/03 18:51:14 by mmagrin          ###   ########.fr       */
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
/*token.c*/
void	ft_populate_token_list(t_token *token, char *line);
/*token_utils.c*/
int		ft_recogn_t(char *line);
t_token	*ft_new_token_node(void);

#endif
