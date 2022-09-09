# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 15:50:50 by yamzil            #+#    #+#              #
#    Updated: 2022/09/08 22:20:25 by sgmira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	minishell.c\
		utils_main.c\
		ft_collector.c\
		./minishell_utils/ft_list_utils_1.c\
		./minishell_utils/ft_list_utils_2.c\
		./minishell_utils/ft_list_utils_3.c\
		./minishell_utils/ft_list_utils_4.c\
		./minishell_utils/ft_list_utils_5.c\
		./parse/ft_preparse.c\
		./parse/ft_parsing.c\
		./parse/parsing_utils.c\
		./parse/ft_checksyntax.c\
		./token/ft_tokenization.c\
		./token/ft_token_utils.c\
		./token/ft_token_utils01.c\
		./token/ft_token_utils02.c\
		./token/ft_token_space.c\
		./builtins/exec_bultins.c\
		./builtins/cd.c\
		./builtins/pwd.c\
		./builtins/env.c\
		./builtins/echo.c\
		./builtins/export.c\
		./builtins/export_utils.c\
		./builtins/export_utils2.c\
		./builtins/export_utils3.c\
		./builtins/unset.c\
		./builtins/exit.c\
		./builtins/exit_utils.c\
		./othercmds/get_path.c\
		./othercmds/execute_cmd.c\
		./othercmds/multi_cmd.c\
		./othercmds/multi_cmd_utils.c\
		./othercmds/multi_cmd_utils2.c\
		ft_redirections.c\
		redirections_utils.c\
		ft_environment.c\
		ft_sighandler.c\
		ft_minishell_utils.c\
		main_checks.c\
		libft/ft_putstr_fd.c\
		libft/ft_strchr.c\
		libft/ft_bzero.c\
		libft/ft_strrchr.c\
		libft/ft_strdup.c\
		libft/ft_strlen.c\
		libft/ft_strncmp.c\
		libft/ft_substr.c\
		libft/ft_strtrim.c\
		libft/ft_isalpha.c\
		libft/ft_isalnum.c\
		libft/ft_split.c\
		libft/ft_strjoin.c\
		libft/ft_strlcpy.c\
		libft/ft_putchar_fd.c\
		libft/ft_putendl_fd.c\
		libft/ft_atoi.c\
		libft/ft_itoa.c\
		libft/ft_isdigit.c\

INC = 	minishell.h
LIB = ../libft
LFLAGS = -L/Users/sgmira/.brew/opt/readline/lib
IFLAGS = -I/Users/sgmira/.brew/opt/readline/include
CFLAGS = -g -Wall -Werror -Wextra $(IFLAGS)

OBJ = $(SRC:.c=.o) 
CC = cc

all : $(NAME)

$(NAME) : $(INC) $(OBJ)
	@$(CC) $(CFLAGS) $(LFLAGS)  -I $(LIB) -lreadline -lncurses $(SRC) -o $(NAME)

clean : 
	@rm -rf $(OBJ)

fclean :
	@rm -rf $(OBJ) $(NAME)
re : fclean all