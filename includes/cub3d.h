/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:37:58 by bruno             #+#    #+#             */
/*   Updated: 2025/02/13 00:52:47 by davioliv         ###   ########.fr       */
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

# define PI 3.14159265359
# define GREEN 0x0000FF00
# define BLACK 0x000000
# define GREY 0x9c9c9c
# define WHITE 0xFFFFFF

# define WIDTH 1600
# define HEIGHT 1000
# define TEXTURE_SIZE 64

typedef struct s_game		t_game;
typedef struct s_player		t_player;
typedef struct s_sprites	t_sprites;
typedef struct s_data		t_data;
typedef struct s_vect		t_vect;
typedef struct s_cast		t_cast;

struct s_sprites
{
	char	*north;
	char	*cnorth;
	char	*south;
	char	*csouth;
	char	*east;
	char	*ceast;
	char	*west;
	char	*cwest;
	int		floor;
	int		ceiling;
	void	*wall;
	void	*player;
};

struct s_cast
{
	t_vect	*delta_dist;
	t_vect	*side_dist;
	t_vect	*map;
	t_vect	*step;
	double	wall_dist;
	double	wall_x;
	int		wall_height;
	int		side;
};

struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits;
	int		len;
	int		endian;
};

struct s_game
{
	t_sprites	*sprites;
	t_player	*player;
	t_data		*data;
	t_vect		*fv;
	t_vect		*pv;
	char		**fmap;
	char		**map;
	char		**flood_map;
	void		*texture;
	int			start_x;
	int			start_y;
	int			max_x;
	int			max_y;
	int			flag;
};

struct s_vect
{
	double	x;
	double	y;
};

struct s_player
{
	double	pos_x;
	double	pos_y;
	t_vect	*angle;
	t_vect	*perp;
};

/*.........map.c..............*/

void			map_init(t_game *game, char *file);
char			**map_read(char *file);
int				map_lines(char *file);
char			**fmap_read(t_game *game);
void			player_fov(t_game *game, char c);

/*.......minimap.c............*/
void			render_images(t_game *game);
void			put_image_to_window(t_game *game, int i, int j);
int				mmap_init(t_game *game);

/*.........mlx.c..............*/
void			minimap_loop(t_game *game);
int				ft_mlx_init(t_game *game);
int				key_handler(int keycode, t_game *game);
int				start_window(t_game *game);
void			mlx_pixel(t_data *data, int x, int y, int color);
void			destroy_images(t_game *game);

/*........flood_fill.c...........*/
int				check_colors(char *input);
int				flood_fill(int x, int y, t_game *game);
int				check_flood_fill(t_game *game);
char			**create_flood_map(t_game *game);
int				flood_map_utils(int start, t_game *game);
int				check_player(char c, t_game *game, int i, int j);

/*........checker.c..............*/
int				check_extension(char *file);
int				check_sprite_syntax(char *sprite);
int				check_rgb(int *color);
int				only_digits(char *input);

/*........vect_utils.c..........*/
t_vect			*new_vect(double x, double y);
void			rotate_vector(t_vect *vector, int degree);
void			perp_vect(t_vect *v1, t_vect *v2);
int				ft_render(t_game *game);
void			create_image(t_game *game);
// void draw_vertical_line(t_game *game, int screen_x, int wall_height, double wall_x, int side);
void			draw_vertical_line(t_game *game, int screen_x, \
				int wall_height, double wall_x, \
				int side, t_vect *ray_dir);
char			*ft_texture(t_game *game, int side, t_vect *ray_dir);

/*........raycasting.c.........*/
void			pixel_put(t_data *data, int x, int y, int color);
unsigned int	get_pixel_color(void *texture, int tex_x, \
			int tex_y, int texture_width);
int				ft_raycasting(t_game *game);

/*.........cleaner.c............*/
void			dp_cleaner(char **var);
void			exit_project(t_game *game, char *msg);
void			clean_project(t_game *game);
int				exit_key(t_game *game);

/*.........sprite.c...............*/
int				color_init(t_game *game, char *line);
int				shift_color(int *rgb);
void			sprites_init(t_game *game);
int				check_if_wall(char *line);

/*.........utils.c...............*/
int				check_invalid_chars(char **map);
int				skip_spaces(char *line);
void			start_sprites(t_game *game);
char			**fmap_utils(t_game *game, int start);
void			draw_wall(t_game *game, int i, int j, int color);
int				set_colors(t_game *game, char *line, int i);
int				set_sprite_walls(t_game *game, char *line, int i);
int				left_utils(t_game *game, int keycode);
int				check_wall(t_game *game, int flag);
int				no_we_alloc(t_game *game, char *line, int i);
void			clean_colors_trash(t_game *game, char *line, \
					char **rgb, char *msg);
int				check_newline(t_game *game, char **map, int i);
char			**alloc_map(int lines, char *file, int fd);
int				reach_map(char **map);

#endif
