/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:31:26 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 16:48:14 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_forward(char *str)
{
	ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	close_extra_fds(void)
{
	int	last_open_fd;

	last_open_fd = open("/tmp/last_fd", O_RDWR | O_CREAT, 0666);
	if (last_open_fd == -1)
		error_msg("open", NULL, "/tmp/last_fd", NULL);
	while (last_open_fd > STDERR_FILENO)
	{
		close(last_open_fd);
		last_open_fd--;
	}
}

void	close_all_fds(void)
{
	close_extra_fds();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	pipe_handler(int original_fd_out, char *current_cmd, char **cmds)
{
	int			first_cmd;
	int			next_cmd;
	char		*last_cmd;
	static int	pipe_fds[2];

	last_cmd = cmds[ft_arraylen(cmds) - 1];
	first_cmd = (current_cmd == cmds[0]);
	next_cmd = (current_cmd != last_cmd);
	if (!first_cmd)
		redirect_fd(pipe_fds[IN], STDIN_FILENO);
	if (next_cmd)
	{
		if (pipe(pipe_fds) == -1)
			error_msg("pipe", NULL, current_cmd, NULL);
		redirect_fd(pipe_fds[OUT], STDOUT_FILENO);
	}
	else
		redirect_fd(original_fd_out, STDOUT_FILENO);
}
