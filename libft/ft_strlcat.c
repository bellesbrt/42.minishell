/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:03:38 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:52:06 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t max_size)
{
	size_t	return_size;

	return_size = 0;
	while (*dst && return_size < max_size)
	{
		dst++;
		return_size++;
	}
	if (return_size >= max_size)
		return (return_size + ft_strlen(src));
	while (*src && return_size + 1 < max_size)
	{
		*dst = *src;
		dst++;
		src++;
		return_size++;
	}
	*dst = '\0';
	return (return_size + ft_strlen(src));
}
