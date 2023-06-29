/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:43:21 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/22 23:32:33 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	external_exit_handler(char **args, t_env *env, int exit_status)
{
	if (exit_status == NOT_EXECUTABLE)
		error_msg(args[0], NOT_EXECUTABLE_MSG, NULL, NULL);
	if (exit_status == CMD_NOT_FOUND)
		error_msg(args[0], CMD_NOT_FOUND_MSG, NULL, NULL);
	rl_clear_history();
	free_env(&env);
	free_array(args);
	close_all_fds();
	exit(exit_status);
}

static int	verify_folder(char *cmd)
{
	struct stat	status;

	if (stat(cmd, &status) != 0)
		return (0);
	if (S_ISDIR(status.st_mode))
	{
		if (*cmd == '.')
			cmd++;
		if (*cmd == '.')
			cmd++;
		if (*cmd == '/')
			return (TRUE);
	}
	return (FALSE);
}

static void	execve_error_handler(char **args, char *path, char **envp)
{
	int	error;

	error = EXIT_FAILURE;
	error_msg("execve", NULL, args[0], NULL);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	free_array(args);
	free_array(envp);
	free(path);
	exit(error);
}

static int	verify_minienv_path(t_env *env)
{
	return (env_value("PATH", env) != NULL);
}

int	exec_external_cmd(char **args, t_env *env)
{
	char	*path;
	char	*cmd;
	char	**envp;

	cmd = args[0];
	if (verify_empty(cmd))
		external_exit_handler(args, env, EXIT_SUCCESS);
	if (verify_folder(cmd))
		external_exit_handler(args, env, NOT_EXECUTABLE);
	path = get_path(cmd, env);
	if (path == NULL && verify_minienv_path(env))
		external_exit_handler(args, env, CMD_NOT_FOUND);
	else if (path == NULL)
		path = ft_strdup(cmd);
	rl_clear_history();
	close_extra_fds();
	envp = env_to_envp(env);
	free_env(&env);
	if (execve(path, args, envp) == -1)
		execve_error_handler(args, path, envp);
	exit(EXIT_SUCCESS);
}
