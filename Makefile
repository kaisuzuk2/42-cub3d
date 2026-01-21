# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suzukikaisei <suzukikaisei@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/03 09:34:20 by suzukikaise       #+#    #+#              #
#    Updated: 2025/12/03 09:39:35 by suzukikaise      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	cc
FLAG	=	-Wall -Werror -Wextra
DEBUG 	=	-g -fsanitize=address

INC		=	-Iincludes -Iminilibx-linux -Ilibft -Iget_next_line
MAKE	= make -C
RM		=	rm -rf

DIR		=	srcs
_SRCS	=	parse.c\
			init.c \
			input.c \
			tex.c \
			player.c \
			ray.c \
			map.c \
			draw.c \
			render.c
SRCS	=	$(addprefix $(DIR)/, $(_SRCS))
OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) minilibx-linux
	$(MAKE) libft bonus
	$(MAKE) get_next_line
	$(CC) -o $(NAME) $(FLAG) $(INC) main.c $(OBJS) -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lbsd -lft -Llibft -lgnl -Lget_next_line

%.o:%.c
	$(CC) $(FLAG) $(INC) -c $< -o $@
	
clean:
	$(MAKE) minilibx-linux clean
	$(MAKE) libft clean
	$(MAKE) get_next_line clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) libft fclean
	$(MAKE) get_next_line fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all

