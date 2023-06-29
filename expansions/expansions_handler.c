/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:29:17 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 15:36:56 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expansions_handler(char **input, t_env *env, int exit_status)
{
	expand_exit_status(input, exit_status);
	expand_variables(input, env);
}
