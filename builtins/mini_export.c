/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:28:01 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 16:09:30 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	declare_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name_only(aux->data_node), STDOUT_FILENO);
		if (ft_strchr(aux->data_node, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(value_only(aux->data_node), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

int	mini_export(char **args, t_env **env)
{
	char	*data_node;
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (declare_env(*env));
	while (*args)
	{
		data_node = *args;
		varname = name_only(data_node);
		if (!validate_var_name(varname) || compare_strings(data_node, "="))
		{
			error_msg("export", NULL, NULL, data_node);
			exit_status = EXIT_FAILURE;
		}
		else if (env_node(varname, *env))
			env_update(varname, value_only(data_node), *env);
		else
			append_node(data_node, env);
		free(varname);
		args++;
	}
	return (exit_status);
}
