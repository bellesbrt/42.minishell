/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:28:09 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 18:28:30 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_error(void)
{
	error_msg("cd", "too many arguments", NULL, NULL);
	return (EXIT_FAILURE);
}

int	mini_cd(char **args, t_env *env)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (args[1] && args[2])
		return (cd_error());
	if (args[1] && !compare_strings(args[1], "~"))
		path = args[1];
	else
		path = env_value("__HOME", env);
	if (chdir(path) != 0)
	{
		error_msg("cd", NULL, args[1], NULL);
		return (EXIT_FAILURE);
	}
	pwd = env_value("PWD", env);
	oldpwd = env_value("OLDPWD", env);
	if (oldpwd && pwd && *pwd)
		env_update("OLDPWD", pwd, env);
	if (pwd && *pwd)
		env_update("PWD", getcwd(cwd, PATH_MAX), env);
	return (EXIT_SUCCESS);
}
