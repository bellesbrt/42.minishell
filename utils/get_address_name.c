/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_address_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:31:35 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/20 00:53:55 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_name_end(char *name)
{
	int	name_end;

	name_end = 0;
	while (name[name_end] && !verify_name_delimeter(name[name_end]))
	{
		if (name[name_end] == '\'')
		{
			move_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '\'')
				name_end++;
			move_forward(&name[name_end]);
		}
		else if (name[name_end] == '"')
		{
			move_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '"')
				name_end++;
			move_forward(&name[name_end]);
		}
		else if (name[name_end] && !verify_name_delimeter(name[name_end]))
			name_end++;
	}
	return (name_end);
}

char	*get_address_name(char *redirect_str)
{
	int		name_start;
	int		name_end;
	char	*name;
	char	*remaining_cmd;

	name_start = 0;
	move_forward(redirect_str);
	if (redirect_str[name_start] == '>')
		move_forward(&redirect_str[name_start]);
	while (redirect_str[name_start] == ' ' || redirect_str[name_start] == '\t')
		name_start++;
	name_end = get_name_end(&redirect_str[name_start]);
	name = ft_substr(&redirect_str[name_start], 0, name_end);
	remaining_cmd = &redirect_str[name_start + name_end];
	ft_memmove(redirect_str, remaining_cmd, ft_strlen(remaining_cmd) + 2);
	return (name);
}
