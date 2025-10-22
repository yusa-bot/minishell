# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/08 19:14:52 by rinka             #+#    #+#              #
#    Updated: 2025/10/23 08:50:40 by ayusa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	builtins/ft_add_env.c \
	builtins/ft_lst_utils.c \
	builtins/ft_env.c \
	builtins/ft_exports.c \
	builtins/ft_unset.c \
	builtins/ft_set_env.c \
	parser/ft_cmdlst_utils.c \
	parser/join_expanded_tokens.c \
	parser/ft_parser_utils.c \
	parser/ft_parser.c \
	parser/ft_redirectlst_utils.c \
	parser/ft_globbing.c \
	parser/ft_heredoc.c \
	tokenizer/ft_tokenizer.c \
	tokenizer/ft_tokenlst_utils.c \
	tokenizer/ft_tokenlst_sort.c \
	utils/ft_free.c \
	utils/ft_utils.c \
	main.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFT_DIR)

INCLUDE = -I./include

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)
	make fclean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
