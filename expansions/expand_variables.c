/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:29:22 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/21 15:36:49 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_var_pos(char *input)
{
	while (*input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && verify_varname(input[1]))
					return (input);
				input++;
			}
		}
		if (*input == '$' && verify_varname(input[1]))
			return (input);
		input++;
	}
	return (NULL);
}

static void	update_input(char **input, char *var_value, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	if (!*input[0] && !var_value)
		first_part = ft_strdup("");
	else if (!*input[0] && var_value)
		first_part = ft_strdup(var_value);
	else if (!var_value)
		first_part = ft_strdup(*input);
	else
		first_part = ft_strjoin(*input, var_value);
	updated_input = ft_strjoin(first_part, second_part);
	free(first_part);
	free(*input);
	*input = updated_input;
}

void	expand_variables(char **input, t_env *env)
{
	char	*var_position;
	char	*var_name;
	char	*var_value;
	int		name_size;

	var_position = find_var_pos(*input);
	if (var_position)
	{
		name_size = 0;
		while (verify_varname(var_position[name_size + 1]))
			name_size++;
		var_name = ft_substr(var_position, 1, name_size);
		*var_position = '\0';
		var_value = env_value(var_name, env);
		update_input(input, var_value, (var_position + 1 + name_size));
		free(var_name);
		expand_variables(input, env);
	}
}
