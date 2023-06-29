/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:00:59 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:49:07 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (src < dst)
	{
		i = n - 1;
		while (n)
		{
			*((char *)dst + i) = *((char *)src + i);
			i--;
			n--;
		}
	}
	else
	{
		i = 0;
		while (n)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
			n--;
		}
	}
	return (dst);
}
