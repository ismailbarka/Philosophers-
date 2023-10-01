# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 18:20:08 by isbarka           #+#    #+#              #
#    Updated: 2023/07/26 19:10:49 by isbarka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philosophers.c ft_atoi.c routine.c init.c 
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
NAME = philo

all : $(NAME)

$(NAME): $(OBJS) philosophers.h
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)
fclean: clean  
	rm -f $(NAME)
re: fclean all