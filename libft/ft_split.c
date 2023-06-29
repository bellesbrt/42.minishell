/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:03:56 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:50:16 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_substrings(char const *s, char c);
static size_t	add_string_to_arr(char **arr, int i, char *s, char c);
void			free_previous_allocations(char **arr, int i);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	substring_size;
	int		i;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (count_substrings(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			substring_size = add_string_to_arr(arr, i, (char *)s, c);
			if (!substring_size)
				return (NULL);
			s += substring_size;
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

size_t	add_string_to_arr(char **arr, int i, char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	arr[i] = malloc(sizeof(char) * (len + 1));
	if (!arr[i])
	{
		free_previous_allocations(arr, i);
		return (0);
	}
	if (!(ft_strlcpy(arr[i], s, len + 1)))
		return (0);
	return (len);
}

int	count_substrings(char const *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

void	free_previous_allocations(char **arr, int i)
{
	while (i--)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}
