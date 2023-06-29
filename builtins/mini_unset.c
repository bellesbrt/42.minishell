/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:27:50 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 16:16:46 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_next_node(t_env **node)
{
	t_env	*temp;

	temp = (*node)->next;
	(*node)->next = ((*node)->next)->next;
	free(temp->data_node);
	free(temp);
}

static void	remove_from_minienv(char *varname, t_env **env)
{
	t_env	*aux;

	aux = *env;
	while (aux && aux->next)
	{
		if (ft_strncmp((aux->next)->data_node,
				varname, ft_strlen(varname)) == 0)
		{
			if ((aux->next)->data_node[ft_strlen(varname)] == '=')
				return (remove_next_node(&aux));
		}
		aux = aux->next;
	}
}

int	mini_unset(char **args, t_env **env)
{
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (0);
	while (*args)
	{
		varname = *args;
		if (!validate_var_name(varname))
		{
			error_msg("unset", NULL, NULL, varname);
			exit_status = EXIT_FAILURE;
		}
		else
			remove_from_minienv(varname, env);
		args++;
	}
	return (exit_status);
}
