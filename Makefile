# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 11:28:01 by ssulkuma          #+#    #+#              #
#    Updated: 2022/09/22 11:14:28 by ssulkuma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SRC_FILES = main.c \
			map.c \
			map_checker.c \
			error.c \
			textures.c \
			draw.c \
			wall_raycasting.c \
			floor_raycasting.c \
			key_events.c \
			mouse_events.c \
			skybox.c \
			objects.c \
			animations.c
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
INCLUDES = -I /usr/local/include -I ./libft
LIB = -L /usr/local/lib -lmlx -L ./libft -lft -lpthread
HOME_INCLUDES = -I ./minilibx -I ./libft
HOME_LIB = -L ./minilibx -lmlx -L ./libft -lft -lpthread
FLAGS = -Wall -Wextra -Werror -O3
FRAMEWORK = -framework OpenGL -framework AppKit
HEADER = wolf3d.h

.PHONY: all clean fclean re home

all: $(NAME)

$(NAME): $(OBJ_FILES) $(HEADER)
	make -C ./libft
	gcc $(FLAGS) -c $(SRC_FILES) $(INCLUDES)
	gcc $(FLAGS) -o $(NAME) $(OBJ_FILES) $(LIB) $(FRAMEWORK)

clean:
	make -C ./libft clean
	/bin/rm -f $(OBJ_FILES)

fclean: clean
	make -C ./libft fclean
	/bin/rm -f $(NAME)

re: fclean all

home: $(OBJ_FILES) $(HEADER)
	make -C ./libft
	gcc $(FLAGS) -c $(SRC_FILES) $(HOME_INCLUDES)
	gcc $(FLAGS) -o $(NAME) $(OBJ_FILES) $(HOME_LIB) $(FRAMEWORK)
