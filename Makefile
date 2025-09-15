# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/08 19:14:52 by rinka             #+#    #+#              #
#    Updated: 2025/09/14 17:58:55 by ayusa            ###   ########.fr        #∆
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = \
	builtins/env_util.c \
	builtins/cmd/ft_env.c \
	builtins/cmd/ft_export.c \
	builtins/cmd/ft_unset.c \
	parser/ft_cmdlst_utils.c \
	parser/join_expanded_tokens.c \
	parser/ft_parser_utils.c \
	parser/ft_parser.c \
	tokenizer/ft_tokenizer.c \
	tokenizer/ft_tokenlst_utils.c \
	ft_free.c \
	main.c \
	signal.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f


LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

# linux
#INCLUDE = -I./include
#LDFLAGS = -lreadline

# mac
INCLUDE = -I./include -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)


clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

# current0:makefileテストできる状態にする
