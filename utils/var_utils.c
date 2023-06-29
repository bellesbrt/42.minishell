/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:31:30 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/20 00:58:03 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	validate_var_name(char *name)
{
	if (!ft_isalpha(*name))
		return (FALSE);
	while (*name)
	{
		if (!verify_varname(*name))
			return (FALSE);
		name++;
	}
	return (TRUE);
}
