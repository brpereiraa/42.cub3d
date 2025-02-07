/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:47:25 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/07 22:48:47 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	calc_textures(t_game *game, int wall_height, int screen_x)
{
	t_vect	*tex;
	double	tex_pos;
	double	step;
	int		start;
	int		end;
}

void	draw_vertical_line(t_game *game, int screen_x, int wall_height, double wall_x, int side, t_vect *ray_dir)
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
		pixel_put(game->data, screen_x, y, get_pixel_color(game->texture, tex->x, tex->y, TEXTURE_SIZE));
	}
	free(tex);
}

void	cast_single_ray(t_game *game, t_vect *ray_dir, int screen_x)
{
	t_vect	*delta_dist;
	t_vect	*side_dist;
	t_vect	*map;
	t_vect	*step;
	int side;

	delta_dist = new_vect(fabs(1 / ray_dir->x), fabs(1 / ray_dir->y));
	side_dist = (t_vect *)malloc(sizeof(t_vect));
	step = (t_vect *)malloc(sizeof(t_vect));
	map = new_vect((int)game->player->pos_x, (int)game->player->pos_y);
	if (ray_dir->x < 0)
	{
		step->x = -1;
		side_dist->x = (game->player->pos_x - map->x) * delta_dist->x;
	}
	else
	{
		step->x = 1;
		side_dist->x = (map->x + 1.0 - game->player->pos_x) * delta_dist->x;
	}
	if (ray_dir->y < 0)
	{
		step->y = -1;
		side_dist->y = (game->player->pos_y - map->y) * delta_dist->y;
	}
	else
	{
		step->y = 1;
		side_dist->y = (map->y + 1.0 - game->player->pos_y) * delta_dist->y;
	}
	while (1)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist->x;
			map->x += step->x;
			side = 0;
		}
		else
		{
			side_dist->y += delta_dist->y;
			map->y += step->y;
			side = 1;
		}
		if (game->fmap[(int)map->y][(int)map->x] == '1')
			break;
	}
	double wall_dist = (side == 0) ? (side_dist->x - delta_dist->x) : (side_dist->y - delta_dist->y);
	int wall_height = (int)(HEIGHT / wall_dist);
	double wall_x;
	if (side == 0)
		wall_x = game->player->pos_y + wall_dist * ray_dir->y;
	else
		wall_x = game->player->pos_x + wall_dist * ray_dir->x;
	wall_x -= floor(wall_x);

	draw_ceiling_floor(game, screen_x, wall_height);
	draw_vertical_line(game, screen_x, wall_height, wall_x, side, ray_dir);
	free(delta_dist);
	free(side_dist);
	free(step);
	free(map);
}

int ft_raycasting(t_game *game)
{
	t_vect	*plane;
	t_vect	*dir;
	t_vect	*ray_dir;
	double	camera_x;
	int		x;
	
	dir = (t_vect *)malloc(sizeof(t_vect));
	plane = (t_vect *)malloc(sizeof(t_vect));
	dir->x = game->player->angle->x;
	dir->y = game->player->angle->y;
	plane->x = game->player->perp->x;
	plane->y = game->player->perp->y;
	ray_dir = (t_vect *)malloc(sizeof(t_vect));
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
	mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0, 0);
	return (1);
}
