/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:37:58 by bruno             #+#    #+#             */
/*   Updated: 2024/11/22 18:49:40 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h" 
# include "../minilibx-linux/mlx_int.h" 
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h> 
# include <math.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

typedef struct s_game t_game;
typedef struct s_player t_player;
typedef struct s_sprites t_sprites;
typedef struct s_data t_data;
typedef struct s_vect t_vect;

struct s_sprites {
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
};

struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int	bits;
	int	len;
	int	endian;
};

struct s_game {
	t_sprites	*sprites;
	t_player	*player;
	t_data		*data;
	t_vect		*fv;
	t_vect		*pv;
	char		**fmap;
	char		**map;
};

struct s_player { 
	double	pos_x;
	double	pos_y;
};

struct s_vect {
	double	x;
	double	y;
};

/*.........map.c..............*/

int	map_init(t_game *game, char *file);
char	**map_read(char *file);
int	map_lines(char *file);
char	**fmap_read(t_game *game);

/*.......minimap.c............*/
void	put_image(t_game *game);
void	put_image_to_window(t_game *game, int i, int j);
int	mmap_init(t_game *game);

/*.........mlx.c..............*/
void	minimap_loop(t_game *game);
int	ft_mlx_init(t_game *game);
int	key_handler(int keycode, t_game *game);
int	start_window(t_game *game);
void	mlx_pixel(t_data *data, int x, int y, int color);
void destroy_images(t_game *game);

/*........checker.c...........*/
int	check_extension(char *file);
// int	file_validation(char *map);
// int	char_validation(char *map);
// int	map_validation(char *map);


int ft_render(t_game *game);
void create_image(t_game *game);

int	ft_raycasting(t_game *game);
#endif

