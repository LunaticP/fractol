# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/11 11:02:36 by aviau             #+#    #+#              #
#    Updated: 2016/10/21 04:22:32 by aviau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

SRC_NAME =	main.c\
			fract.c\
			mandel.c\
			julia.c\
			bship.c\
			graphic.c\
			spiral.c\
			key.c

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC=-I./include -I./libft -I ./libmlx
ARG=-L./libft -lft -lmlx -lpthread -framework OpenGl -framework AppKit
CFLAGS = -Wall -Wextra -Werror
all: $(NAME)
	@printf "\e[33m$(NAME)\t\e[32m[OK]\n"

$(NAME): lib $(OBJ)
	@gcc $(CFLAGS) $(ARG) $(INC) $(OBJ) -o $@

lib:
	@make -C ./libft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	-@mkdir -p $(OBJ_PATH)
	@gcc $(CFLAGS) -c -o $@ $< $(INC)

clean:
	-@rm -rf $(OBJ_PATH)
	@make -C ./libft $@

fclean: clean
	-@rm $(NAME)
	@make -C ./libft $@
	@printf "\e[33m$(NAME)\e[31m cleaned\n"


re: fclean all

.PHONY: fclean clean
