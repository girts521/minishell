/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattiamagrin <mattiamagrin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:11:26 by mmagrin           #+#    #+#             */
/*   Updated: 2025/07/26 16:31:57 by mattiamagri      ###   ########.fr       */
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
	TOKEN_EOF,			// End marker (optional)
	TOKEN_UNCLOSEDQUOTES
} t_token_type;

typedef struct s_token {
	t_token_type	type ;	// Type of token
	char			*value;	// Raw string (e.g., "echo", ">", "hello $USER")
	struct s_token	*next;	// Next token in the list
} t_token;

/*token.c*/
t_token	*ft_new_token_node(void);
int		ft_select_token(t_token **token, char *line, t_token_type type);
void	ft_populate_token_list(t_token *token, char *line);
/*token_utils.c*/
int		ft_recogn_t(char *line);
int		ft_sdquote(t_token **token, char *line, t_token_type type);
int		ft_here_app(t_token **token, char *line, t_token_type type);
int		ft_redir_pipe(t_token **token, char *line, t_token_type type);
int		ft_word(t_token **token, char *line);
/*free_token_list.c*/
void	ft_free_token_list(t_token *token);

#endif
