# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 15:50:50 by yamzil            #+#    #+#              #
#    Updated: 2022/08/25 18:28:53 by sgmira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -g -Wall -Werror -Wextra

CC = cc

HEADER = minishell.h \

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)

READLINE = $(shell brew --prefix readline)

SRC =	minishell.c\
		./minishell_utils/ft_list_utils_2.c\
		./minishell_utils/ft_list_utils_3.c\
		./minishell_utils/ft_list_utils_4.c\
		./parse/ft_preparse.c\
		./parse/ft_parsing.c\
		./parse/ft_checksyntax.c\
		./token/ft_tokenization.c\
		./token/ft_token_utils.c\
		./token/ft_token_utils01.c\
		./builtins/exec_bultins.c\
		./builtins/cd.c\
		./builtins/pwd.c\
		./builtins/env.c\
		./builtins/echo.c\
		./builtins/export.c\
		./builtins/unset.c\
		./othercmds/get_path.c\
		./othercmds/execute_cmd.c\
		./othercmds/multi_cmd.c\
		ft_redirections.c\
		ft_environment.c\
		ft_sighandler.c\
		ft_minishell_utils.c\
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
		libft/ft_atoi.c\
		libft/ft_itoa.c\
		# ft_checkcmd.c\
		# ./builtins/cd.c\
		# ./builtins/echo.c\
		# ./builtins/env.c\
		# ./builtins/pwd.c\
		# ./builtins/unset.c\
		# ./builtins/echo_cheker.c\

OBJS = $(SRC:.c=.o)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE_READLINE) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDE_READLINE)  -L $(LIB_READLINE) -o $(NAME) -lreadline
	clear

clean : 
	rm -f $(OBJS)
	clear

fclean : clean
	rm -f $(NAME)
	clear

re : fclean all
