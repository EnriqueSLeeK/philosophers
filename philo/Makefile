# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 22:03:20 by ensebast          #+#    #+#              #
#    Updated: 2022/03/26 00:14:15 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CFLAGS := -g #-Werror -Wextra -Wall
CC := clang

LIB := -lpthread

FILES := init.c main.c free_up.c check.c util.c\
		 feast.c
OBJ := $(addprefix ./obj/, $(FILES:c=o))

.PHONY: all clean fclean re

all: $(NAME)

./obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf ./obj

re: fclean all
