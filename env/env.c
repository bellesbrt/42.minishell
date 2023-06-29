/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:37:29 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 16:10:46 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_data_node(char *name, char *value)
{
	char	*data_node;
	int		data_node_size;
	int		i;

	data_node_size = ft_strlen(name) + ft_strlen(value) + 2;
	data_node = malloc(data_node_size * sizeof(char));
	i = 0;
	while (*name)
		data_node[i++] = *name++;
	data_node[i++] = '=';
	while (*value)
		data_node[i++] = *value++;
	data_node[i] = '\0';
	return (data_node);
}

void	env_update(char *name, char *value, t_env *env)
{
	t_env	*aux;
	char	*new_data_node;
	int		size;
	int		i;

	aux = env_node(name, env);
	if (!aux)
	{
		new_data_node = create_data_node(name, value);
		append_node(new_data_node, &env);
		free(new_data_node);
		return ;
	}
	free(aux->data_node);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	new_data_node = malloc(size * sizeof(char));
	i = 0;
	while (*name)
		new_data_node[i++] = *name++;
	new_data_node[i++] = '=';
	while (*value)
		new_data_node[i++] = *value++;
	new_data_node[i] = '\0';
	aux->data_node = new_data_node;
}

void	append_node(char *data_node, t_env **list)
{
	struct s_env	*new_node;
	struct s_env	*aux_node;

	new_node = malloc(sizeof(struct s_env));
	new_node->data_node = ft_strdup(data_node);
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	aux_node = *list;
	while (aux_node->next)
		aux_node = aux_node->next;
	aux_node->next = new_node;
}

t_env	*env_node(char *name, t_env *env)
{
	t_env	*aux;
	int		size;

	aux = env;
	size = ft_strlen(name);
	while (aux)
	{
		if (ft_strncmp(name, aux->data_node, size) == 0)
		{
			if (aux->data_node[size] == '=')
				return (aux);
		}
		aux = aux->next;
	}
	return (NULL);
}

t_env	*init_env(char **envp)
{
	t_env	*list;
	char	*home;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		append_node(envp[i], &list);
		i++;
	}
	if (!env_node("OLDPWD", list))
		append_node("OLDPWD", &list);
	home = ft_strjoin("__HOME=", env_value("HOME", list));
	append_node(home, &list);
	free(home);
	return (list);
}
