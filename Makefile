# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 23:22:06 by vsozonof          #+#    #+#              #
#    Updated: 2024/01/08 06:02:25 by vsozonof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -g3

BL=\033[1;34m
GR=\033[1;32m
OR=\033[1;33m
RD=\033[1;31m
WH=\033[0m

SRCS_LIB = libft/libft.a \

SRCS = main.c \
	   parsing/get_input.c \
	   parsing/init_struct.c \
	   parsing/input_parser.c \
	   parsing/args_parser.c \
	   free/free_1.c \
	   utils/args_counter.c \
	   utils/flags_counter.c \
	   utils/pipe_utils.c \
	   utils/pipes_splitter.c \
	   signal/sig_handler.c \
	   Exec/command_manager.c \
	   Exec/command_overall.c \
	   Exec/execute.c \
	   Builtin/cd.c \
	   Builtin/echo.c \
	   Builtin/pwd.c \
	   Builtin/env.c \
	   Builtin/exit.c \

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: init $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(RD)MINISHELL -\t$(WH)$(BL)Linking $(OR)($<)$(WH)\r"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(SRCS_LIB)
	@echo "                                   \r\c"

%.o: %.c
	@echo "$(RD)MINISHELL -\t$(WH)$(BL)Compiling $(OR)($<)$(WH)\c\r"
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "                                   \r\c"

init:
	make all -C ./libft

clean:
		make clean -C ./libft
		@$(RM) $(OBJS)
		@echo "$(RD)MINISHELL -\t$(WH)$(GR)All .o files were deleted !$(WH)"

fclean: 
		make fclean -C ./libft
		@$(RM) $(NAME) $(OBJS)
		@echo "$(RD)MINISHELL -\t$(WH)$(GR)All .o files and binaries were deleted !$(WH)"

re: fclean all

.PHONY: all clean fclean re init