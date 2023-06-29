/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:34:38 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/22 23:35:24 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	one_redirect_handler(char *cmd, int original_fds[2])
{
	char	redirect;

	original_fds[IN] = NO_REDIRECT;
	original_fds[OUT] = NO_REDIRECT;
	redirect = get_next_redirect(cmd);
	while (redirect)
	{
		if (redirect == '<')
		{
			if (!fd_redirect_handler(cmd, original_fds, 0))
				return (FAILED);
		}
		if (redirect == '>')
		{
			if (!fd_redirect_handler(cmd, original_fds, 1))
				return (FAILED);
		}
		if (redirect < 0)
		{
			save_original_fd(original_fds, 0);
			redirect_heredoc(cmd, redirect);
		}
		redirect = get_next_redirect(cmd);
	}
	return (SUCCESS);
}

static void	one_restore_original_fds(int original_fds[2])
{
	if (original_fds[IN] != NO_REDIRECT)
		redirect_fd(original_fds[IN], STDIN_FILENO);
	if (original_fds[OUT] != NO_REDIRECT)
		redirect_fd(original_fds[OUT], STDOUT_FILENO);
}

int	exec_forked_external(char **args, t_env *env)
{
	int		child_pid;
	char	*cmd;

	cmd = args[0];
	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		error_msg("fork", NULL, cmd, NULL);
	else if (child_pid == 0)
		exec_external_cmd(args, env);
	else
		return (wait_for_child(child_pid, TRUE));
	exit(EXIT_FAILURE);
}

int	exec_one_cmd(char *cmd, t_env **env)
{
	char	**args;
	int		exit_status;
	int		original_fds[2];

	if (!one_redirect_handler(cmd, &original_fds[0]))
	{
		one_restore_original_fds(original_fds);
		free(cmd);
		return (EXIT_FAILURE);
	}
	args = split_args(cmd);
	free(cmd);
	if (builtin_checker(args[0]))
		exit_status = identify_run_builtin(args, env);
	else
		exit_status = exec_forked_external(args, *env);
	free_array(args);
	one_restore_original_fds(original_fds);
	return (exit_status);
}
