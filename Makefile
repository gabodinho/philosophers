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

CFLAGS  := -Wall -Werror -Wextra -fsanitize=thread -g
#CFLAGS  := -Wall -Werror -Wextra -g
HEADERS	:= -I include
SRCS 	:=	philo_utils.c \
			philo_utils2.c \
			philo_helpers.c \
			philo_main.c \
			philo_mutex.c \
			philo_threads.c \
			philo_monitoring.c
OBJS	:= ${SRCS:.c=.o}
NAME	:= philo

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: clean all

.PHONY: all, clean, fclean, re
