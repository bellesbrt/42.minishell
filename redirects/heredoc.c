/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:30:35 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 16:34:15 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*tmp_filename(int heredoc_number)
{
	char	filename[30];
	char	*number_str;

	ft_bzero(filename, 30);
	number_str = ft_itoa(heredoc_number);
	ft_strlcat(filename, "/tmp/heredoc", 30);
	ft_strlcat(filename, number_str, 30);
	free(number_str);
	return (ft_strdup(filename));
}

void	redirect_heredoc(char *cmd, int heredoc_number)
{
	char	*filename;
	int		tmp_file_fd;
	char	*heredoc_position;

	filename = tmp_filename(heredoc_number);
	tmp_file_fd = open(filename, O_RDONLY);
	if (tmp_file_fd == -1)
	{
		error_msg("open", NULL, filename, NULL);
		free(filename);
		return ;
	}
	free(filename);
	redirect_fd(tmp_file_fd, STDIN_FILENO);
	heredoc_position = get_redirect_position(cmd, heredoc_number);
	move_forward(heredoc_position);
}

int	redirect_input(char *cmd)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = get_redirect_position(cmd, '<');
	if (!input_redirect)
		return (SUCCESS);
	file_name = get_address_name(input_redirect);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		error_msg("open", NULL, file_name, NULL);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (SUCCESS);
}

int	redirect_output(char *cmd)
{
	char	*output_redirect;
	char	*file_name;
	int		fd;
	int		open_flags;

	output_redirect = get_redirect_position(cmd, '>');
	if (!output_redirect)
		return (SUCCESS);
	if (output_redirect[1] == '>')
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	file_name = get_address_name(output_redirect);
	fd = open(file_name, open_flags, 0644);
	if (fd == -1)
	{
		error_msg("open", NULL, file_name, NULL);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDOUT_FILENO);
	free(file_name);
	return (SUCCESS);
}
