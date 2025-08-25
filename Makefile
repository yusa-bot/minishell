# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rinka <rinka@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/08 19:14:52 by rinka             #+#    #+#              #
#    Updated: 2025/08/25 08:58:34 by rinka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	builtins/ft_add_env.c \
	builtins/ft_envlst_utils.c \
	builtins/ft_put_envs.c \
	builtins/ft_put_exports.c \
	builtins/ft_unset.c \
	builtins/set_env.c \
	tokenizer/ft_tokenizer.c \
	tokenizer/ft_tokenlst_utils.c \
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

# current0:makefileテストできる状態にする
