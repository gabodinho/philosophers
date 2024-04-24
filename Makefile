# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 19:51:00 by ggiertzu          #+#    #+#              #
#    Updated: 2024/04/22 10:53:47 by irivero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS  := -g -O0 -fsanitize=thread -Wall -Werror -Wextra
CC		:= cc
HEADERS	:= -I include
SRCS 	:= phil_utils.c 
OBJS	:= ${SRCS:.c=.o}
NAME	:= philo

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: clean all

.PHONY: all, clean, fclean, re
