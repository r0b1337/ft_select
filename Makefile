# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdurst <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 16:16:42 by rdurst            #+#    #+#              #
#    Updated: 2018/09/13 04:02:12 by rdurst           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_select
CC=gcc
INCLUDES= -I ./includes -I ./libft/includes/
LIBFT= libft/libft.a
SRCS= ./srcs/main.c\
	./srcs/list.c\
	./srcs/cursor.c\
	./srcs/keys.c\
	./srcs/signal_handler.c\

OPTIONS= -Wall -Wextra -Werror -ltermcap
RM= rm -rf

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

$(NAME):
	@make -C libft
	@$(CC) $(SRCS) $(INCLUDES) $(LIBFT) -o $(NAME) $(OPTIONS)
	@echo "$(BLUE)\t\t\t\tft_select has been built.$(RESET)"

clean:
	@make -C libft fclean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)\t\t\t\tft_select has been removed.$(RESET)"

re: fclean all

all: $(NAME)
