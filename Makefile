# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lafontai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/23 09:39:28 by lafontai          #+#    #+#              #
#    Updated: 2020/04/12 15:31:19 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(addprefix $(FOLDER), main.c scene.c camera.c light.c parsing.c parse_utils.c parse_identifier.c parse_shape.c window.c event.c color.c vector.c ray.c intersection.c shape.c plane.c sphere.c square.c)

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
			cd libft/ && make bonus
			cd minilibx/ && make
			mv minilibx/libmlx.dylib .
			$(CC) $(CFLAGS) libft/libft.a libmlx.dylib $(OBJS) -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

clean:
			make clean -C libft/
			make clean -C minilibx/
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C libft/
			$(RM) libmlx.dylib
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
