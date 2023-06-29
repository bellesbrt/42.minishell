/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:30:59 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 15:37:32 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_heredoc_position(char *str)
{
	while (*str && str[1])
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '<' && str[1] == '<')
			return (str);
		str++;
	}
	return (NULL);
}

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

void	read_heredoc(int *exit_status, t_env *env, char *delim,
		int heredoc_number)
{
	char	*line_read;
	char	*filename;
	int		tmp_file_fd;

	filename = tmp_filename(heredoc_number);
	tmp_file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	line_read = readline("> ");
	while (line_read && !compare_strings(line_read, delim))
	{
		expand_exit_status(&line_read, *exit_status);
		expand_variables(&line_read, env);
		ft_putstr_fd(line_read, tmp_file_fd);
		ft_putchar_fd('\n', tmp_file_fd);
		free(line_read);
		line_read = readline("> ");
	}
	if (!line_read)
		error_msg("warning: heredoc delimited by EOF. Wanted",
			delim, NULL, NULL);
	cleanup_heredoc(env, line_read, tmp_file_fd, delim);
	exit(EXIT_SUCCESS);
}

int	exec_heredoc(char *delim, int heredoc_number, int *exit_status,
		t_env *env)
{
	int	child_pid;

	child_pid = fork();
	define_heredoc_signals(child_pid);
	if (child_pid == -1)
		error_msg("fork - heredoc_prompt", NULL, delim, NULL);
	else if (child_pid == 0)
		read_heredoc(exit_status, env, delim, heredoc_number);
	else
	{
		*exit_status = wait_for_child(child_pid, TRUE);
		define_main_signals();
		if (*exit_status != EXIT_SUCCESS)
			return (FAILED);
	}
	return (SUCCESS);
}

int	heredoc_handler(char *input, int *exit_status, t_env *env)
{
	static int	heredoc_number;
	char		*heredoc_position;
	char		*delim;

	heredoc_number = -1;
	heredoc_position = get_heredoc_position(input);
	if (!heredoc_position)
		return (SUCCESS);
	heredoc_number--;
	*heredoc_position = heredoc_number;
	heredoc_position++;
	delim = get_address_name(heredoc_position);
	if (!exec_heredoc(delim, heredoc_number, exit_status, env))
	{
		free(delim);
		return (FAILED);
	}
	free(delim);
	return (heredoc_handler(input, exit_status, env));
}
