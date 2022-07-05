# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 22:03:20 by ensebast          #+#    #+#              #
#    Updated: 2022/07/05 14:58:02 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CFLAGS := -Werror -Wextra -Wall
CC := clang

LIB := -lpthread

FILES := main.c action.c sim.c init.c alloc_util.c\
		 check_num.c free_util.c util.c\
		 wait_phil.c critical_reg.c
		 
OBJ := $(addprefix ./obj/, $(FILES:c=o))

.PHONY: all clean fclean re

all: $(NAME)

./obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LIB) -o $@ $(OBJ)

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf ./obj

re: fclean all
