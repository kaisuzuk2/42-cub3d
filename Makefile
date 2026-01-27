# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/03 09:34:20 by suzukikaise       #+#    #+#              #
#    Updated: 2026/01/27 14:24:15 by kaisuzuk         ###   ########.fr        #
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
			parse_config.c \
			parse_map.c \
			parse_valid_map.c \
			parse_utils.c \
			parse_player.c \
			parse_color.c \
			init.c \
			event.c \
			tex.c \
			player.c \
			ray.c \
			ray_init.c \
			ray_dda.c \
			ray_utils.c \
			map.c \
			render.c \
			render_calc.c \
			error.c \
			dispose.c
SRCS	=	$(addprefix $(DIR)/, $(_SRCS))
OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) main.c
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

