# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 11:28:31 by ayusa             #+#    #+#              #
#    Updated: 2025/09/15 12:00:56 by ayusa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_free_str_array.c ft_isdelimit.c ft_strcmp.c ft_strjoin_safe.c ft_strndup.c ft_strspn.c

LST_SOURCES = lst/ft_lst_add_back.c lst/ft_lst_add_front.c lst/ft_lst_clear.c lst/ft_lst_delone.c lst/ft_lst_last.c lst/ft_lst_new.c

ALL_SOURCES = $(SOURCES) $(LST_SOURCES)
OBJECTS = $(ALL_SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./lst

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
