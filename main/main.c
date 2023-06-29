/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:30:55 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/22 23:55:59 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_input_error(char *input, int *exit_status, t_env *env)
{
	int	result;

	result = FALSE;
	if (verify_empty(input))
		result = TRUE;
	else if (verify_unclosed_quotes(input))
		result = TRUE;
	else if (invalid_syntax_handler(input))
	{
		*exit_status = 2;
		result = TRUE;
	}
	else if (heredoc_handler(input, exit_status, env) == FAILED)
		result = TRUE;
	if (result == TRUE)
		free(input);
	return (result);
}

char	*get_prompt_str(t_env *env)
{
	char		*user;
	char		*cwd;
	char		*directory;
	static char	prompt[PATH_MAX];

	user = env_value("USER", env);
	if (!user)
		user = "UNKNOWN";
	cwd = env_value("PWD", env);
	if (!cwd)
		cwd = "/UNKNOWN";
	directory = ft_strrchr(cwd, '/') + 1;
	if (ft_strncmp(cwd, "/", 2) == 0)
		directory = "ROOT";
	ft_bzero(prompt, sizeof(prompt));
	ft_strlcat(prompt, BLU, PATH_MAX);
	ft_strlcat(prompt, user, PATH_MAX);
	ft_strlcat(prompt, WHT, PATH_MAX);
	ft_strlcat(prompt, "@", PATH_MAX);
	ft_strlcat(prompt, YEL, PATH_MAX);
	ft_strlcat(prompt, directory, PATH_MAX);
	ft_strlcat(prompt, CRESET, PATH_MAX);
	ft_strlcat(prompt, ":", PATH_MAX);
	return (prompt);
}

char	*prompt_input(t_env *env)
{
	char	*input;

	input = readline(get_prompt_str(env));
	if (!input)
		mini_exit(NULL, &env);
	if (input && *input)
		add_history(input);
	return (input);
}

int	minishell(t_env *env)
{
	int		exit_status;
	char	*input;
	char	**cmds;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		define_main_signals();
		input = prompt_input(env);
		if (has_input_error(input, &exit_status, env))
			continue ;
		expansions_handler(&input, env, exit_status);
		if (!verify_pipe(input))
			exit_status = exec_one_cmd(input, &env);
		else
		{
			cmds = split_commands(input);
			free(input);
			exit_status = exec_multi_cmd(cmds, &env);
			free_array(cmds);
		}
	}
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	if (argv && argc > 1)
	{
		ft_putstr_fd("Does not accept arguments", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (minishell(init_env(envp)));
}
