# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 17:34:39 by inicole-          #+#    #+#              #
#    Updated: 2023/06/22 23:51:15 by inicole-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -g
LDLIBS	=	-lreadline -lft
LDFLAGS	+= 	-L./libft
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	$(MAIN) $(ENV) $(BUILTINS) $(EXEC) $(REDIRECTS) $(UTILS) \
			$(EXPANDS) $(SYNTAX)

BUILTINS =	mini_echo.c mini_cd.c mini_pwd.c mini_export.c mini_unset.c mini_env.c mini_exit.c
ENV		=	env.c env_utils.c env_utils2.c
EXEC	 =	exec_one_cmd.c exec_multi_cmd.c wait_for_children.c \
			exec_external_cmd.c forked_builtin_handler.c split_args.c get_path.c \
			one_utils.c multi_utils.c
EXPANDS	=	expansions_handler.c expand_exit_status.c expand_variables.c
REDIRECTS =	redirect_utils.c heredoc.c
MAIN	=	main.c split_commands.c heredoc_handler.c heredoc_utils.c
SYNTAX	=	syntax.c syntax_utils.c
UTILS	=	error.c quotes.c signals.c utils.c verify.c \
			get_address_name.c var_utils.c

LIBFT_A	=	./libft/libft.a
HEADER	=	minishell.h
VPATH	=	builtins env utils exec main redirects expansions \
			syntax

all: $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf obj

fclean: clean
	@rm -rf $(NAME)

re: fclean all

$(LIBFT_A):
	make --directory=./libft

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

leak: all
	valgrind --suppressions=./local.supp --leak-check=full \
	--show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(NAME)