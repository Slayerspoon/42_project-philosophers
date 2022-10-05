# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 21:03:25 by aionescu          #+#    #+#              #
#    Updated: 2022/03/01 22:36:34 by aionescu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = philosophers_main.c input_check.c philosopher_actions.c \
		philosophers_monitor.c philosophers_utils_1.c philosophers_utils_2.c \
		philosopher_sim_checks.c

all: $(NAME)

$(NAME):
	$(CC) -Wall -Wextra -Werror $(SRC) -o $(NAME)
	rm -f *.o
	chmod a+x $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
