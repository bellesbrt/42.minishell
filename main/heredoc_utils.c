/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:37:40 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 15:37:46 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_heredoc(t_env *env, char *line_read,
		int tmp_file_fd, char *delim)
{
	close(tmp_file_fd);
	free(line_read);
	free(delim);
	free_env(&env);
	rl_clear_history();
}
