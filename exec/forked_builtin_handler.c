/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_builtin_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:27 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/22 23:36:56 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_checker(char *cmd)
{
	if (!cmd)
		return (0);
	if (compare_strings(cmd, "cd"))
		return (1);
	if (compare_strings(cmd, "echo"))
		return (1);
	if (compare_strings(cmd, "env"))
		return (1);
	if (compare_strings(cmd, "exit"))
		return (1);
	if (compare_strings(cmd, "export"))
		return (1);
	if (compare_strings(cmd, "pwd"))
		return (1);
	if (compare_strings(cmd, "unset"))
		return (1);
	return (0);
}

int	identify_run_builtin(char **args, t_env **env)
{
	char	*cmd;

	cmd = args[0];
	if (compare_strings(cmd, "cd"))
		return (mini_cd(args, *env));
	if (compare_strings(cmd, "echo"))
		return (mini_echo(args));
	if (compare_strings(cmd, "env"))
		return (mini_env(*env));
	if (compare_strings(cmd, "exit"))
		return (mini_exit(args, env));
	if (compare_strings(cmd, "export"))
		return (mini_export(args, env));
	if (compare_strings(cmd, "pwd"))
		return (mini_pwd());
	if (compare_strings(cmd, "unset"))
		return (mini_unset(args, env));
	else
		return (EXIT_FAILURE);
}

int	forked_builtin_handler(char **args, t_env **env)
{
	int	exit_status;

	exit_status = identify_run_builtin(args, env);
	free_array(args);
	free_env(env);
	rl_clear_history();
	exit(exit_status);
}
