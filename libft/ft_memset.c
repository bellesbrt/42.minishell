/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:00:56 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:49:22 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int value, size_t len)
{
	unsigned char	*str;

	str = p;
	while (len)
	{
		*str = (unsigned char)value;
		str++;
		len--;
	}
	return (p);
}
