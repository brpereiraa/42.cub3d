/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:47:25 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/25 19:50:53 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	get_raydata(t_game *game, t_cast *data)
{
	(void)game;
	data->start = -data->wall_height / 2 + HEIGHT / 2;
	data->end = data->wall_height / 2 + HEIGHT / 2;
	if (data->start < 0)
		data->start = 0;
	if (data->end >= HEIGHT)
		data->end = HEIGHT - 1;
}

void	draw_vertical_line(t_game *game, int screen_x, \
			t_cast *data, t_vect *ray_dir)
{
	t_vect	*tex;
	double	tex_pos;
	int		y;

	tex = (t_vect *)malloc(sizeof(t_vect));
	get_raydata(game, data);
	game->texture = ft_texture(game, data->side, ray_dir);
	tex->x = (int)(data->wall_x * (double)TEXTURE_SIZE);
	if (data->side == 0 && ray_dir->x < 0)
		tex->x = TEXTURE_SIZE - tex->x - 1;
	else if (data->side == 1 && ray_dir->y > 0)
		tex->x = TEXTURE_SIZE - tex->x - 1;
	data->sstep = 1.0 * TEXTURE_SIZE / data->wall_height;
	tex_pos = (data->start - HEIGHT / 2 + data->wall_height / 2) * data->sstep;
	y = data->start;
	while (y++ < data->end)
	{
		tex->y = (int)tex_pos & (TEXTURE_SIZE - 1);
		tex_pos += data->sstep;
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

	data = (t_cast *)malloc(sizeof(t_cast));
	data->delta_dist = new_vect(fabs(1 / ray_dir->x), fabs(1 / ray_dir->y));
	data->side_dist = (t_vect *)malloc(sizeof(t_vect));
	data->step = (t_vect *)malloc(sizeof(t_vect));
	map = new_vect((int)game->player->pos_x, (int)game->player->pos_y);
	initialize_side_and_step(ray_dir, data, game, map);
	data->side = perform_dda(data, map, game);
	calculate_wall_distance_and_x(data, data->side, ray_dir, game);
	draw_ceiling_floor(game, screen_x, data->wall_height);
	draw_vertical_line(game, screen_x, data, ray_dir);
	free(data->delta_dist);
	free(data->side_dist);
	free(data->step);
	free(data);
	free(map);
}
