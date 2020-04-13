# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lafontai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/23 09:39:28 by lafontai          #+#    #+#              #
#    Updated: 2020/03/23 10:40:47 by lafontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(shell find . -name '*.c' | grep -v lst)

A_SRCS	= $(shell find . -name '*.c')

OBJS	= $(SRCS:.c=.o)

A_OBJS	= $(A_SRCS:.c=.o)

NAME	= libft.a

RM		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

ifeq ($(DEBUG), true)
	CFLAGS += -g -fsanitize=address
endif

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

bonus:		$(A_OBJS)
			ar rcs $(NAME) $(A_OBJS)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(A_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
