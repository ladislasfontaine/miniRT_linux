# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/23 09:39:28 by lafontai          #+#    #+#              #
#    Updated: 2020/05/14 13:10:30 by lafontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(addprefix $(FOLDER), \
			main.c \
			scene.c \
			camera.c \
			light.c \
			parsing.c \
			parse_utils.c \
			parse_identifier.c \
			parse_shape.c \
			window.c \
			event.c \
			color.c \
			vector.c \
			ray.c \
			intersection.c \
			shape.c \
			plane.c \
			sphere.c \
			triangle.c \
			cylinder.c \
			square.c)

OBJS	= $(SRCS:.c=.o)

FOLDER	= sources/

INCS	= includes/

NAME	= miniRT

RM		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

ifeq ($(DEBUG), true)
	CFLAGS += -g -fsanitize=address
endif

all:		$(NAME)

$(NAME):	$(OBJS)
			cd libftprintf/ && make
			cd minilibx/ && make
			mv minilibx/libmlx.dylib .
			$(CC) $(CFLAGS) libftprintf/libftprintf.a libmlx.dylib $(OBJS) -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

clean:
			make clean -C libftprintf/
			make clean -C minilibx/
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C libftprintf/
			$(RM) libmlx.dylib
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
