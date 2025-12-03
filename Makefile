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

RM		=	rm -rf

_SRCS	=	
SRCS	=	$(addprefix $(DIR)/, $(_SRCS))
OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) -o $(NAME) $(FLAG) main.c $(OBJS)

%.o:%.c
	$(CC) $(FLAG) -c $< -o $@
	
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all

