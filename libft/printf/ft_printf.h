/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:22:58 by mmagrin           #+#    #+#             */
/*   Updated: 2024/11/25 17:41:41 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*							Librarys*/
/*# include <stddef.h>*/
# include <stdlib.h>
# include <stdio.h>
/*# include <string.h>*/
/*# include <limits.h>*/
# include <unistd.h>
/*# include <fcntl.h>*/
# include <stdint.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
/*								char*/
int	ft_printf_c(char c);
/*								str*/
int	ft_printf_s(char *str);
/*								dec*/
int	ft_printf_d_i(int num);
int	ft_printf_u(unsigned int num);
/*								hex*/
int	ft_printf_p(void *ptr);
int	ft_printf_x(unsigned int num);
int	ft_printf_xx(unsigned int num);

#endif
