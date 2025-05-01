# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 10:37:24 by myokono           #+#    #+#              #
#    Updated: 2025/05/01 12:27:16 by myokono          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# ライブラリ
LIBFT_DIR = srcs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = srcs/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# インクルードディレクトリ
INC_DIR = includes
INC = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

# ソースファイル
SRC_DIR = srcs
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/init/init_mlx.c \
      $(SRC_DIR)/init/init_player.c \
      $(SRC_DIR)/init/init_texture.c \
      $(SRC_DIR)/parser/map_parser.c \
      $(SRC_DIR)/parser/map_parser_utils.c \
      $(SRC_DIR)/parser/map_checker.c \
      $(SRC_DIR)/parser/player.c \
      $(SRC_DIR)/parser/config_parser.c \
      $(SRC_DIR)/utils/utils.c \
      $(SRC_DIR)/raycasting/raycasting.c \
      $(SRC_DIR)/raycasting/calculate_ray.c \
      $(SRC_DIR)/raycasting/calculate_wall.c \
      $(SRC_DIR)/render/render.c \
      $(SRC_DIR)/input/input.c \
      $(SRC_DIR)/input/input_rotate.c \
      $(SRC_DIR)/input/input_move.c \
      $(SRC_DIR)/utils/cleanup.c \
      $(SRC_DIR)/utils/get_next_line.c \
	  

# オブジェクトファイル
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re