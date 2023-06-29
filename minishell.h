/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:04:18 by inicole-          #+#    #+#             */
/*   Updated: 2023/06/23 16:12:20 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h" // libft
# include <stdio.h> // perror
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // getpwd
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags

# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"

# define IN 0
# define OUT 1

# define BLU	"\001\e[0;34m\002"
# define YEL	"\001\e[0;33m\002"
# define WHT	"\001\e[0;37m\002"
# define CRESET	"\001\e[0m\002"

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define PATH_MAX	4096
# define LLONG_MAX 9223372036854775807

# define NO_REDIRECT -1

typedef struct s_env
{
	char			*data_node;
	struct s_env	*next;
}				t_env;

//builtins
int			mini_cd(char **args, t_env *env);
int			mini_echo(char **args);
int			mini_pwd(void);
int			mini_export(char **args, t_env **env);
int			mini_env(t_env *envp);
int			mini_unset(char **args, t_env **env);
int			mini_exit(char **args, t_env **env);

//env
t_env		*init_env(char **envp);
t_env		*env_node(char *name, t_env *env);
char		*env_value(char *name, t_env *env);
void		env_update(char *name, char *value, t_env *env);
void		append_node(char *data_node, t_env **list);
char		**env_to_envp(t_env *env);
void		free_env(t_env **env);
char		*create_data_node(char *name, char *value);
char		*name_only(char *data_node);
char		*value_only(char *data_node);

//exec
char		**split_args(char *cmd);
int			exec_one_cmd(char *cmd, t_env	**env);
int			exec_multi_cmd(char **cmds, t_env **env);
void		save_original_fd(int original_fds[2], int flag);
int			fd_redirect_handler(char *cmd, int original_fds[2], int flag);
int			*init_children_pid(char **cmds);
void		clean_after_execute(int *children_pid);
void		quit_child(char **cmds, t_env **env);
int			forked_builtin_handler(char **args, t_env **env);
int			identify_run_builtin(char **args, t_env **env);
int			exec_external_cmd(char **args, t_env *env);
char		*get_path(char *cmd, t_env *env);
int			wait_for_child(int child_pid, int is_last_child);
int			wait_for_children(int children_pid[1024]);
int			builtin_checker(char *cmd);

//expansions
void		expansions_handler(char **input, t_env *env, int exit_status);
void		expand_variables(char **input, t_env *env);
void		expand_exit_status(char **input, int exit_status);

//main
int			minishell(t_env	*env);
char		*prompt_input(t_env *env);
int			has_input_error(char *input, int *exit_status, t_env *env);
int			heredoc_handler(char *input, int *exit_status, t_env *env);
char		**split_commands(char *input);
void		cleanup_heredoc(t_env *env, char *line_read,
				int tmp_file_fd, char *delim);

//redirects
void		redirect_fd(int fd_to_redirect, int fd_location);
void		redirect_fds(int fd_in, int fd_out);
int			redirect_input(char *cmd);
int			redirect_output(char *cmd);
char		*get_redirect_position(char *str, char redirect_char);
char		get_next_redirect(char *str);
void		close_extra_fds(void);
char		*get_address_name(char *redirect_str);
void		redirect_heredoc(char *cmd, int heredoc_number);

//syntax
int			invalid_syntax_handler(char *input);
int			verify_invalid_token(char c);
int			syntax_error(char *token);
char		*get_next_pipe(char *str);

//utils
int			verify_unclosed_quotes(char *str);
void		define_main_signals(void);
void		define_execute_signals(int child_pid);
void		define_heredoc_signals(int child_pid);
int			compare_strings(const char *str1, const char *str2);
int			verify_quote(char c);
int			verify_empty(char *str);
int			verify_name_delimeter(char c);
int			verify_pipe(char *str);
void		free_array(char **arr);
void		move_forward(char *str);
int			skip_quotes(char *str);
void		close_all_fds(void);
void		exit_with_error(char *cmd, char *msg, int error);
void		exit_with_perror(char *cmd, char *perror_msg, int error);
void		error_msg(char *cmd, char *msg,
				char *perror_msg, char *varname);
int			verify_varname(char c);
int			validate_var_name(char *name);
void		pipe_handler(int original_out, char *current_cmd,
				char **cmds);

#endif