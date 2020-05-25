# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/23 09:39:28 by lafontai          #+#    #+#              #
#    Updated: 2020/05/21 16:03:45 by lafontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(addprefix $(FOLDER), \
			main.c \
			scene.c \
			camera.c \
			delete.c \
			light.c \
			parsing.c \
			parse_utils.c \
			parse_identifier.c \
			parse_shape.c \
			window.c \
			event.c \
			color.c \
			color_utils.c \
			vector1.c \
			vector2.c \
			vector3.c \
			ray.c \
			intersection.c \
			image.c \
			save.c \
			shape.c \
			plane.c \
			sphere.c \
			triangle.c \
			cylinder.c \
			square.c)

OBJS	= $(SRCS:.c=.o)

FOLDER	= sources/

INCS	= includes/

MLX		= minilibx-linux/

INC_LIB	= libft/includes/

NAME	= miniRT

RM		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -lm -lbsd -lX11 -lXext

ifeq ($(DEBUG), true)
	CFLAGS += -g -fsanitize=address
endif

all:		$(NAME)

$(NAME):	$(OBJS)
			cd libft/ && make
			cd $(MLX) && make
			$(CC) -o $(NAME) -I$(INCS) -I$(INC_LIB) -I$(MLX) $(OBJS) libft/libft.a $(MLX)libmlx.a $(MLX)libmlx_Linux.a $(CFLAGS)

%.o:		%.c
			$(CC) $(CFLAGS) -c -I$(INCS) -I$(INC_LIB) -I$(MLX) $< -o $@

clean:
			make clean -C libft/
			make clean -C minilibx-linux/
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C libft/
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
