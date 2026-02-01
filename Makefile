# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 18:20:38 by aghalmi           #+#    #+#              #
#    Updated: 2026/02/01 18:56:10 by aghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/main.c \
       srcs/lexical_analyzer/lexical_analyzer.c \
       srcs/lexical_analyzer/lexical_analyzer_utils.c \
	   srcs/lexical_analyzer/lexical_analyzer_pipe.c \
	   srcs/lexical_analyzer/lexical_analyzer_redir.c \
	   srcs/lexical_analyzer/lexical_analyzer_quote.c \
	   srcs/lexical_analyzer/lexical_analyzer_logical.c \
	   srcs/parsing/parsing.c \
	   srcs/parsing/parsing_utils.c \
	   srcs/parsing/parsing_utils_2.c \
	   srcs/parsing/check_syntax.c \
	   srcs/parsing/check_syntax_logical.c \
	   srcs/parsing/check_syntax_main.c \
	   srcs/parsing/parsing_logical.c \
	   srcs/expansion/expansion.c \
	   srcs/expansion/expansion_utils.c \
	   srcs/expansion/expansion_variable.c \
	   srcs/expansion/expansion_special.c \
	   srcs/builtin/builtin_pwd.c \
	   srcs/builtin/builtin.c \
	   srcs/builtin/builtin_echo.c \
	   srcs/builtin/builtin_cd.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -Iinclude -Ilibft
LIBS = -Llibft -lft -lreadline

LIBFT = libft/libft.a

GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET = \033[0;39m
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -C libft
	@echo "$(GREEN)✓ libft compiled!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) ready!$(RESET)"

%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	@echo "$(RED)Full clean...$(RESET)"
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re