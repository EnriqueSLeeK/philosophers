# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 22:03:20 by ensebast          #+#    #+#              #
#    Updated: 2022/04/19 01:15:18 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CFLAGS := -g -Werror -Wextra -Wall
CC := clang

LIB := -lpthread

FILES := init.c main.c mem_util.c check.c util.c\
		 feast.c mutex_init.c eat.c sleep_think.c
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
