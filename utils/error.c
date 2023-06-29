/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:31:44 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 16:34:41 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with_perror(char *cmd, char *perror_msg, int error)
{
	error_msg(cmd, NULL, perror_msg, NULL);
	close_all_fds();
	rl_clear_history();
	exit(error);
}

void	exit_with_error(char *cmd, char *msg, int error)
{
	error_msg(cmd, msg, NULL, NULL);
	close_all_fds();
	rl_clear_history();
	exit(error);
}

void	error_msg(char *cmd, char *msg,
char *perror_msg, char *varname)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (msg != NULL)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (varname != NULL)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(varname, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	else if (perror_msg != NULL)
	{
		perror(perror_msg);
	}
}
