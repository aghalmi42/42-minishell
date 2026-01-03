# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 18:20:38 by aghalmi           #+#    #+#              #
#    Updated: 2026/01/03 18:25:31 by aghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME : minishell

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g3 -I./include

LIBS = -lreadline -lhistory

SRCS =

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus