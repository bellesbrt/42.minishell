/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:00:51 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:48:48 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_chars;
	const unsigned char	*s2_chars;

	s1_chars = s1;
	s2_chars = s2;
	while (n)
	{
		if (*s1_chars != *s2_chars)
			return ((unsigned char)*s1_chars - (unsigned char)*s2_chars);
		s1_chars++;
		s2_chars++;
		n--;
	}
	return (0);
}
