#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/16 16:40:23 by gtorresa          #+#    #+#              #
#*   Updated: 2016/08/20 12:06:51 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

NAME = fdf

LIB_DIR = ./libft
LIB_MLX_DIR = ./minilibx

LIB_NAME = $(LIB_DIR)/libft.a 
LIB_JPEG = ./libjpeg

CFLAGS=-Wall -Wextra -Werror -g

SRCS_DIR = ./srcs/

SRCS = $(SRCS_DIR)main.c
SRCS += $(SRCS_DIR)draw_line.c
SRCS += $(SRCS_DIR)print_line.c
SRCS += $(SRCS_DIR)action.c
SRCS += $(SRCS_DIR)tool.c
SRCS += $(SRCS_DIR)frame_info.c
SRCS += $(SRCS_DIR)read_map.c
SRCS += $(SRCS_DIR)init_x11.c
SRCS += $(SRCS_DIR)read_move_space.c
SRCS += $(SRCS_DIR)color_map.c
SRCS += $(SRCS_DIR)mutex.c
SRCS += $(SRCS_DIR)make_png.c


#MINILIBX = -Lminilibx -lmlx -framework OpenGL -framework AppKit
MINILIBX = -L./mlx -lmlx -lXext -lX11 -lm

all: ${NAME}

$(NAME):
	@echo "Make lib_ft"
	@make -C $(LIB_DIR)
	#@echo "Make lib_mlx"
	#@make -C $(LIB_MLX_DIR)
	@echo "Make FDF"
	gcc -o $(NAME) $(SRCS) -I./includes -L$(LIB_DIR) -L$(LIB_JPEG) -lft -ljpeg -lpthread $(MINILIBX)

clean:
	@rm -f $(NAME)
	@echo "Delete $(NAME)"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(LIB_NAME)
	@echo "Delete $(LIB_NAME)"
	@make -C $(LIB_MLX_DIR) clean
	@echo "Delete $(LIB_MLX_DIR)"

re: fclean all
