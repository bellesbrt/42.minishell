/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:31:09 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/20 20:06:40 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_without_address(char *input)
{
	char	*redirect_position;
	char	next_redirect;

	next_redirect = get_next_redirect(input);
	redirect_position = get_redirect_position(input, next_redirect);
	if (!redirect_position)
		return (FALSE);
	if (redirect_position[0] == '<' && redirect_position[1] == '<')
		redirect_position++;
	else if (redirect_position[0] == '>' && redirect_position[1] == '>')
		redirect_position++;
	redirect_position++;
	while (*redirect_position == ' ' || *redirect_position == '\t')
		redirect_position++;
	if (*redirect_position == '\0')
		return (syntax_error("newline"));
	if (verify_invalid_token(*redirect_position))
	{
		redirect_position[1] = '\0';
		return (syntax_error(redirect_position));
	}
	return (redirect_without_address(redirect_position));
}

int	verify_empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	if (!next_pipe)
		return (FALSE);
	next_pipe++;
	while (*next_pipe == ' ' || *next_pipe == '\t')
		next_pipe++;
	if (*next_pipe == '|')
		return (syntax_error("|"));
	return (verify_empty_pipe(next_pipe));
}

int	verify_pipe_at_start(char *input)
{
	if (input[0] == '|')
		return (syntax_error("|"));
	return (FALSE);
}

int	invalid_syntax_handler(char *input)
{
	if (verify_pipe_at_start(input))
		return (TRUE);
	if (redirect_without_address(input))
		return (TRUE);
	if (verify_empty_pipe(input))
		return (TRUE);
	return (FALSE);
}
