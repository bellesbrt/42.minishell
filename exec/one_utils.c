/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:44:03 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 16:29:13 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_original_fd(int original_fds[2], int flag)
{
	if (original_fds[IN] == NO_REDIRECT && flag == 0)
		original_fds[IN] = dup(STDIN_FILENO);
	if (original_fds[OUT] == NO_REDIRECT && flag == 1)
		original_fds[OUT] = dup(STDOUT_FILENO);
}

int	fd_redirect_handler(char *cmd, int original_fds[2], int flag)
{
	if (flag == 0)
	{
		save_original_fd(original_fds, 0);
		if (redirect_input(cmd) == FAILED)
		{
			redirect_fd(original_fds[IN], STDIN_FILENO);
			return (FAILED);
		}
		return (SUCCESS);
	}
	else
	{
		save_original_fd(original_fds, 1);
		if (redirect_output(cmd) == FAILED)
		{
			redirect_fd(original_fds[OUT], STDOUT_FILENO);
			return (FAILED);
		}
		return (SUCCESS);
	}
}
