/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:44:10 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 16:29:05 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*init_children_pid(char **cmds)
{
	int		*children_pid;
	size_t	size;

	size = sizeof(int) * (ft_arraylen(cmds) + 1);
	children_pid = malloc(size);
	if (!children_pid)
		return (NULL);
	ft_bzero(children_pid, size);
	return (children_pid);
}

void	clean_after_execute(int *children_pid)
{
	close_extra_fds();
	free(children_pid);
}

void	quit_child(char **cmds, t_env **env)
{
	rl_clear_history();
	free_env(env);
	free_array(cmds);
	close_all_fds();
	exit(EXIT_FAILURE);
}
