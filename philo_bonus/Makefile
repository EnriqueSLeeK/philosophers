# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 22:03:20 by ensebast          #+#    #+#              #
#    Updated: 2022/07/04 18:15:42 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus

CFLAGS := -Werror -Wextra -Wall
CC := clang

LIB := -lpthread

FILES := main_bonus.c action_bonus.c sim_bonus.c init_bonus.c alloc_util_bonus.c\
		 check_num_bonus.c free_util_bonus.c util_bonus.c\
		 termination_util_bonus.c
		 
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
