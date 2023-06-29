/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:28:37 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 16:28:59 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	mk_path(char base[], char *part1, char *part2, char *part3)
{
	*base = 0;
	ft_strlcat(base, part1, PATH_MAX);
	ft_strlcat(base, part2, PATH_MAX);
	ft_strlcat(base, part3, PATH_MAX);
}

static int	verify_path(char *cmd)
{
	if (*cmd == '.')
		cmd++;
	if (*cmd == '.')
		cmd++;
	if (*cmd == '/')
		return (TRUE);
	return (FALSE);
}

static char	*mk_local_path(char *cmd, t_env *env)
{
	char	full_path[PATH_MAX];

	if (*cmd == '/')
		return (ft_strdup(cmd));
	full_path[0] = 0;
	mk_path(full_path, env_value("PWD", env), "/", cmd);
	return (ft_strdup(full_path));
}

char	*get_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	current_path[PATH_MAX];
	char	**paths_start;

	if (verify_path(cmd))
		return (mk_local_path(cmd, env));
	path_env = env_value("PATH", env);
	paths = ft_split(path_env, ':');
	paths_start = paths;
	while (paths && *paths)
	{
		mk_path(current_path, *paths, "/", cmd);
		if (access(current_path, F_OK) == 0)
		{
			free_array(paths_start);
			return (ft_strdup(current_path));
		}
		paths++;
	}
	free_array(paths_start);
	return (NULL);
}
