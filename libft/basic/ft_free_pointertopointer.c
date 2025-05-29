/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pointertopointer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:50:18 by mmagrin           #+#    #+#             */
/*   Updated: 2025/03/16 16:57:59 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

void	ft_free_pointertopointer(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
