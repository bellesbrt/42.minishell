/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:00:16 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:45:13 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_in_number(int n);
static int	ft_power(int n, int power);

char	*ft_itoa(int n)
{
	char	*str;
	char	*str_start;
	int		digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = digits_in_number(n);
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (NULL);
	str_start = str;
	if (n < 0 && digits--)
	{
		*str++ = '-';
		n *= -1;
	}
	while (n >= 0 && digits--)
	{
		*str++ = '0' + (n / ft_power(10, digits));
		n = n % ft_power(10, digits);
	}
	*str = '\0';
	return (str_start);
}

static int	digits_in_number(int n)
{
	if (n < 0 && n / 10 == 0)
		return (2);
	if (n / 10 == 0)
		return (1);
	return (1 + digits_in_number(n / 10));
}

static int	ft_power(int n, int power)
{
	if (power == 0)
		return (1);
	return (n * ft_power(n, power - 1));
}
