/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:36:24 by mmagrin           #+#    #+#             */
/*   Updated: 2025/01/06 14:30:55 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

int	ft_word_counter(char const *s, char c)
{
	int	word;
	int	i;

	if (!s)
		return (0);
	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word++;
		i++;
	}
	return (word);
}

char	*ft_allocate_and_copy(char const *s, int start, int end)
{
	char	*sub_str;
	int		len;

	len = end - start;
	sub_str = ft_calloc((len + 1), sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_memcpy(sub_str, s + start, len);
	sub_str[len] = '\0';
	return (sub_str);
}

void	ft_free_split(char **str_split, int j)
{
	while (j >= 0)
		free(str_split[j--]);
	free(str_split);
}

char	**ft_substr_creation(char **str_split, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
		{
			str_split[j] = ft_allocate_and_copy(s, start, i + 1);
			if (!str_split[j])
			{
				ft_free_split(str_split, j - 1);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	str_split[j] = NULL;
	return (str_split);
}

char	**ft_split(char const *s, char c)
{
	char	**str_split;

	if (!s)
		return (NULL);
	str_split = ft_calloc((ft_word_counter(s, c) + 1), sizeof(char *));
	if (!str_split)
		return (NULL);
	str_split = ft_substr_creation(str_split, s, c);
	return (str_split);
}
/*
int	main(void)
{
	char **result;
	int i;

	// Test 1: Basic input
	result = ft_split("Hello World 42", ' ');
	for (i = 0; result[i]; i++)
		printf("%s\n", result[i]);
	ft_free_split(result, i - 1);
	// Test 2: Multiple delimiters
	result = ft_split("   Hello   World   42   ", ' ');
	for (i = 0; result[i]; i++)
		printf("%s\n", result[i]);
	ft_free_split(result, i - 1);
	// Test 3: Edge case - empty string
	result = ft_split("", ' ');
	printf("%s\n", result ? "(empty array)" : "(null)");
	// Test 4: Edge case - no delimiters
	result = ft_split("Hello", 'l');
	for (i = 0; result[i]; i++)
		printf("%s\n", result[i]);
	ft_free_split(result, i - 1);
	return (0);
}
*/
