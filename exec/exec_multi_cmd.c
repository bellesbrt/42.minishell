/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:34:34 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/22 23:34:54 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	store_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

static void	multi_redirect_handler(char *cmd, char **cmds, t_env **env)
{
	char	redirect;

	redirect = get_next_redirect(cmd);
	while (redirect)
	{
		if (redirect == '<')
		{
			if (redirect_input(cmd) == FAILED)
				quit_child(cmds, env);
		}
		if (redirect == '>')
		{
			if (redirect_output(cmd) == FAILED)
				quit_child(cmds, env);
		}
		if (redirect < 0)
			redirect_heredoc(cmd, redirect);
		redirect = get_next_redirect(cmd);
	}
}

static void	exec_forked_command(char *cmd, char **cmds,
		t_env **env)
{
	char	**args;

	close_extra_fds();
	args = split_args(cmd);
	free_array(cmds);
	if (builtin_checker(args[0]))
		forked_builtin_handler(args, env);
	else
		exec_external_cmd(args, *env);
}

static void	multi_restore_original_fds(int original_fds[2])
{
	redirect_fd(original_fds[IN], STDIN_FILENO);
	redirect_fd(original_fds[OUT], STDOUT_FILENO);
}

int	exec_multi_cmd(char **cmds, t_env **env)
{
	int	original_fds[2];
	int	*children_pid;
	int	i;

	store_original_fds(original_fds);
	children_pid = init_children_pid(cmds);
	i = 0;
	while (cmds[i])
	{
		pipe_handler(original_fds[OUT], cmds[i], cmds);
		children_pid[i] = fork();
		define_execute_signals(children_pid[i]);
		if (children_pid[i] == -1)
			error_msg("fork", NULL, cmds[i], NULL);
		else if (children_pid[i] == 0)
		{
			free(children_pid);
			multi_redirect_handler(cmds[i], cmds, env);
			exec_forked_command(cmds[i], cmds, env);
		}
		i++;
	}
	multi_restore_original_fds(original_fds);
	return (wait_for_children(children_pid));
}
