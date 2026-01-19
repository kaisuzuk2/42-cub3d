# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 17:32:28 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/07/22 23:09:18 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libgnl.a
CC		=	cc -Wall -Werror -Wextra

MAKE	=	make -C
RM		=	rm -rf 

SRCS	=	get_next_line.c \
			get_next_line_utils.c
		
BSRCS	=	get_next_line_bonus.c \
			get_next_line_bonus_utils.c

OBJS = $(SRCS:%.c=%.o)
BOBJS = $(BSRCS:%.c=%.o)

all: $(NAME)
	
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus : $(BOBJS)
	$(RM) $(NAME)
	ar rcs $(NAME) $(BOBJS)

%.o: %.c
	$(CC) -c -o $@  $<

clean :
	$(RM) $(OBJS)
	$(RM) $(BOBJS)

fclean : clean
	$(RM) $(NAME)

re : clean fclean all

.PHONY: clean fclean bonus all
	