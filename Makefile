# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 23:22:06 by vsozonof          #+#    #+#              #
#    Updated: 2023/11/15 11:28:41 by vsozonof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
FLAGS = -Wall -Werror -Wextra -Iincludes -g3

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

SRCS_LIB = libft/libft.a \

SRCS = main.c \

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: init $(NAME)

$(NAME): $(SRCS) $(OBJS)
	@echo "Compiling ($<)\c\r"
	$(CC) $(FLAGS) $(OBJS) $(SRCS_LIB) -o $(NAME)
	@echo "                                   \r\c" 

init:
	make all -C ./libft

clean:
		@echo "$(COLOUR_GREEN)****** INITIATING CLEAN  ******$(COLOUR_END)"
		make clean -C ./libft
		$(RM) $(OBJS)
		@echo "$(COLOUR_GREEN)******   CLEAN COMPLETE  ******$(COLOUR_END)"

fclean: 
		@echo "$(COLOUR_GREEN)****** INITIATING FCLEAN ******$(COLOUR_END)"
		make fclean -C ./libft
		$(RM) $(NAME) $(OBJS)
		@echo "$(COLOUR_GREEN)******  FCLEAN COMPLETE  ******$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re init