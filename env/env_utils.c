/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:36:59 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 16:08:15 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	env_size(t_env *env)
{
	size_t	size;
	t_env	*aux;

	size = 0;
	aux = env;
	while (aux)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}

char	*env_value(char *name, t_env *env)
{
	t_env	*aux;

	aux = env_node(name, env);
	if (!aux)
		return (NULL);
	return (value_only(aux->data_node));
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*aux;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	aux = env;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(aux->data_node);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
