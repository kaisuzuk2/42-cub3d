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

INC		=	-Iincludes -Iminilibx-linux
MAKE	= make -C
RM		=	rm -rf

DIR		=	srcs
_SRCS	=	tex.c
SRCS	=	$(addprefix $(DIR)/, $(_SRCS))
OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) minilibx-linux
	$(CC) -o $(NAME) $(FLAG) $(INC) main.c $(DEBUG) $(OBJS) -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lbsd

%.o:%.c
	$(CC) $(FLAG) $(INC) -c $< -o $@
	
clean:
	$(MAKE) minilibx-linux clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all

