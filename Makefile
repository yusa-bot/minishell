# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rinka <rinka@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/08 19:14:52 by rinka             #+#    #+#              #
#    Updated: 2025/10/23 23:14:11 by rinka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = \
	main.c \
	signal.c \
	pipe.c \
	redirect.c \
	child_external_search_path.c \
	ft_free_handle.c \
	builtins/env_util.c \
	builtins/env_lst_utils.c \
	builtins/cmd/ft_cd.c \
	builtins/cmd/ft_echo.c \
	builtins/cmd/ft_env.c \
	builtins/cmd/ft_exit.c \
	builtins/cmd/ft_export.c \
	builtins/cmd/ft_pwd.c \
	builtins/cmd/ft_unset.c \
	exec_buildin/buildin.c \
	exec_buildin/child_builtin.c \
	exec_buildin/parent_builtin.c \
	parser/ft_cmdlst_utils.c \
	parser/join_expanded_tokens.c \
	parser/ft_parser_utils.c \
	parser/ft_parser.c \
	parser/ft_redirectlst_utils.c \
	parser/ft_heredoc.c \
	tokenizer/ft_tokenizer.c \
	tokenizer/ft_tokenlst_utils.c \
	tokenizer/ft_tokenlst_sort.c \
	utils/ft_free.c \
	utils/ft_utils.c \
	#parser/ft_globbing.c \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# linux
# INCLUDE = -I./include
# LDFLAGS = -lreadline

# yusa_mac
 INCLUDE = -I./include -I/opt/homebrew/opt/readline/include
 LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

#	rinka_mac
# INCLUDE = -I./include -I/usr/local/opt/readline/include
# LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

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
