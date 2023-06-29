/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:03:25 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:53:34 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*location;

	i = 0;
	location = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			location = ((char *)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (location);
}
