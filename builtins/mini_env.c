/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:28:05 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 16:08:51 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strchr(aux->data_node, '='))
		{
			ft_putstr_fd(aux->data_node, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		aux = aux->next;
	}
	return (0);
}
