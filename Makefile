# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bruno <bruno@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:09:52 by bruno             #+#    #+#              #
#    Updated: 2025/01/30 22:02:48 by davioliv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

MLXFLAGS = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm
#CFLAGS = -Wall -Wextra -Werror -Iincludes
CFLAGS = -Iincludes
SRC = src/main.c src/mlx.c src/key_handling.c src/map/map.c src/map/minimap.c src/map/checker.c \
		src/map/sprite.c src/raycasting/raycasting.c src/raycasting/render.c  src/raycasting/utils.c \
		src/vector/vect_utils.c src/cleaner.c src/map/flood_fill.c src/utils.c

OBJS = $(SRC:.c=.o)
LIBFT = libft
LIBFT_N = libft/libft.a

DOWNLOAD = https://cdn.intra.42.fr/document/document/25858/minilibx-linux.tgz
MLX = ./minilibx-linux

all: $(NAME)

$(NAME): $(OBJS)
	@echo "SRC = $(SRC)"
	@echo "OBJS = $(OBJS)"
	@echo "MLXFLAGS = $(MLXFLAGS)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LIBFT_N = $(LIBFT_N)"
	$(MAKE) --no-print-directory -C $(LIBFT)
	$(MAKE) -C $(MLX)
	cc -g $(OBJS) $(CFLAGS) $(MLXFLAGS) $(LIBFT_N) -o $(NAME)

update:
	@if [ ! -d $(MLX) ]; then \
		echo " Downloading mlx..."; \
		mkdir -p $(MLX); \
		wget $(DOWNLOAD) -O "./minilibx-linux.tgz"; \
		tar -xzvf "./minilibx-linux.tgz" -C .; \
		rm -fr "./minilibx-linux.tgz"; \
	else \
		echo "Folder already exists"; \
	fi

uclean:
	rm -fr $(MLX)

clean:
	$(MAKE) --no-print-directory -C $(LIBFT) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) --no-print-directory -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.SILENT:	

.PHONY: all clean fclean re

