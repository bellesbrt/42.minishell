/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:37:20 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 16:08:25 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*name_only(char *data_node)
{
	int	i;

	i = 0;
	while (data_node[i] != '=' && data_node[i])
		i++;
	return (ft_substr(data_node, 0, i));
}

char	*value_only(char *data_node)
{
	int	i;

	i = 0;
	while (data_node[i] != '=' && data_node[i])
		i++;
	if (!data_node[i])
		return (NULL);
	return (&data_node[i + 1]);
}

void	free_env(t_env **env)
{
	t_env	*aux;
	t_env	*next;

	aux = *env;
	while (aux)
	{
		free(aux->data_node);
		next = aux->next;
		free(aux);
		aux = next;
	}
	env = NULL;
}
