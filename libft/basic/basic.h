/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:21:56 by mmagrin           #+#    #+#             */
/*   Updated: 2025/03/16 16:53:20 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_H
# define BASIC_H

/*							Librarys*/
/*# include <stddef.h>*/
# include <stdlib.h>
# include <stdio.h>
/*# include <string.h>*/
/*# include <limits.h>*/
# include <unistd.h>
/*# include <fcntl.h>*/
# include <stdint.h>
/*# include <stdarg.h>*/

/*							Structures*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*							Character Functions*/
/*Character Classification*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(unsigned char c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isin(int c, char const *set);
/*Character Tranformation*/
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_abs(int nbr);

/*							String Functions*/
/*Lenght*/
int		ft_strlen(const char *str);
int		ft_digitcount(int nbr);
/*Copy and Concatenate*/
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
/*String Extranction*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
/*String Search*/
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(char *big, char *little, size_t len);
/*String Compare*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);

/*							Memory Functions*/
/*Setting and Zeroing*/
void	*ft_memset(void	*s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
/*Copying and Moving*/
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
/*Memory Search and Compare*/
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(void *s1, void *s2, size_t n);

/*							Free functions*/
void	ft_free_pointertopointer(char **s);

/*							Conversion Functions*/
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

/*							Allocation Functions*/
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);

/*							File Descritors*/
/*Characters*/
void	ft_putchar_fd(char c, int fd);
/*Strings*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
/*Intigers*/
void	ft_putnbr_fd(int n, int fd);

/*							list*/
/*Creation*/
t_list	*ft_lstnew(void *content);
/*Manipulation*/
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*Deliting*/
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

#endif
