/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:47:25 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/08 19:39:43 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_wall_distance_and_x(t_cast *data, \
			int side, t_vect *ray_dir, t_game *game);

void	initialize_side_and_step(t_vect *ray_dir, \
			t_cast *data, t_game *game, t_vect *map)
{
	if (ray_dir->x < 0)
	{
		data->step->x = -1;
		data->side_dist->x = (game->player->pos_x - map->x) \
			* data->delta_dist->x;
	}
	else
	{
		data->step->x = 1;
		data->side_dist->x = (map->x + 1.0 - game->player->pos_x) \
			* data->delta_dist->x;
	}
	if (ray_dir->y < 0)
	{
		data->step->y = -1;
		data->side_dist->y = (game->player->pos_y - map->y) \
			* data->delta_dist->y;
	}
	else
	{
		data->step->y = 1;
		data->side_dist->y = (map->y + 1.0 - game->player->pos_y) \
			* data->delta_dist->y;
	}
}

void	draw_ceiling_floor(t_game *game, int screen_x, int wall_height)
{
	int	y;
	int	start;
	int	end;

	start = -wall_height / 2 + HEIGHT / 2;
	end = wall_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = -1;
	while (++y < start)
		pixel_put(game->data, screen_x, y, game->sprites->ceiling);
	y = end - 1;
	while (++y < HEIGHT)
		pixel_put(game->data, screen_x, y, game->sprites->floor);
}

void	draw_vertical_line(t_game *game, int screen_x, \
			int wall_height, double wall_x, int side, t_vect *ray_dir)
{
	t_vect	*tex;
	double	step;
	double	tex_pos;
	int		start;
	int		end;

	tex = (t_vect *)malloc(sizeof(t_vect));
	start = -wall_height / 2 + HEIGHT / 2;
	end = wall_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	game->texture = ft_texture(game, side, ray_dir);
	tex->x = (int)(wall_x * (double)TEXTURE_SIZE);
	if (side == 0 && ray_dir->x < 0)
		tex->x = TEXTURE_SIZE - tex->x - 1;
	else if (side == 1 && ray_dir->y > 0)
		tex->x = TEXTURE_SIZE - tex->x - 1;
	step = 1.0 * TEXTURE_SIZE / wall_height;
	tex_pos = (start - HEIGHT / 2 + wall_height / 2) * step;
	for (int y = start; y < end; y++)
	{
		tex->y = (int)tex_pos & (TEXTURE_SIZE - 1);
		tex_pos += step;
		pixel_put(game->data, screen_x, y, \
			get_pixel_color(game->texture, tex->x, tex->y, TEXTURE_SIZE));
	}
	free(tex);
}

int	perform_dda(t_cast *data, t_vect *map, t_game *game)
{
	int	side;

	while (1)
	{
		if (data->side_dist->x < data->side_dist->y)
		{
			data->side_dist->x += data->delta_dist->x;
			map->x += data->step->x;
			side = 0;
		}
		else
		{
			data->side_dist->y += data->delta_dist->y;
			map->y += data->step->y;
			side = 1;
		}
		if (game->fmap[(int)map->y][(int)map->x] == '1')
			break ;
	}
	return (side);
}

void	cast_single_ray(t_game *game, t_vect *ray_dir, int screen_x)
{
	t_cast	*data;
	t_vect	*map;
	int		side;
	double	wall_dist;

	data = (t_cast *)malloc(sizeof(t_cast));
	data->delta_dist = new_vect(fabs(1 / ray_dir->x), fabs(1 / ray_dir->y));
	data->side_dist = (t_vect *)malloc(sizeof(t_vect));
	data->step = (t_vect *)malloc(sizeof(t_vect));
	map = new_vect((int)game->player->pos_x, (int)game->player->pos_y);
	initialize_side_and_step(ray_dir, data, game, map);
	side = perform_dda(data, map, game);
	calculate_wall_distance_and_x(data, side, ray_dir, game);
	draw_ceiling_floor(game, screen_x, data->wall_height);
	draw_vertical_line(game, screen_x, data->wall_height, \
		data->wall_x, side, ray_dir);
	free(data->delta_dist);
	free(data->side_dist);
	free(data->step);
	free(data);
	free(map);
}

void	calculate_wall_distance_and_x(t_cast *data, \
			int side, t_vect *ray_dir, t_game *game)
{
	double	wall_dist;

	if (side == 0)
		wall_dist = data->side_dist->x - data->delta_dist->x;
	else
		wall_dist = data->side_dist->y - data->delta_dist->y;
	if (side == 0)
		data->wall_x = game->player->pos_y + wall_dist * ray_dir->y;
	else
		data->wall_x = game->player->pos_x + wall_dist * ray_dir->x;
	data->wall_x -= floor(data->wall_x);
	if (side == 0)
		wall_dist = data->side_dist->x - data->delta_dist->x;
	else
		wall_dist = data->side_dist->y - data->delta_dist->y;
	data->wall_height = (int)(HEIGHT / wall_dist);
}

int	ft_raycasting(t_game *game)
{
	t_vect	*plane;
	t_vect	*dir;
	t_vect	*ray_dir;
	double	camera_x;
	int		x;

	ray_dir = (t_vect *)malloc(sizeof(t_vect));
	dir = new_vect(game->player->angle->x, game->player->angle->y);
	plane = new_vect(game->player->perp->x, game->player->perp->y);
	x = -1;
	while (++x < WIDTH)
	{
		camera_x = 1 - 2 * x / (double)WIDTH;
		ray_dir->x = dir->x + plane->x * camera_x;
		ray_dir->y = dir->y + plane->y * camera_x;
		cast_single_ray(game, ray_dir, x);
	}
	free(ray_dir);
	free(dir);
	free(plane);
	mlx_put_image_to_window(game->data->mlx,
		game->data->win, game->data->img, 0, 0);
	return (1);
}
