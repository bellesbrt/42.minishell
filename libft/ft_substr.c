/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:03:20 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:53:52 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	char	*substring_start;
	size_t	s_size;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (len > s_size)
		len = s_size;
	substring = malloc(sizeof(*s) * len + 1);
	if (!substring)
		return (NULL);
	while (*s && start--)
		s++;
	substring_start = substring;
	while (*s && len)
	{
		*substring = *s;
		substring++;
		s++;
		len--;
	}
	*substring = '\0';
	return (substring_start);
}
