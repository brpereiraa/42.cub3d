/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:54 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/16 18:06:30 by brpereir         ###   ########.fr       */
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

char	*ft_texture(t_game *game, int side, t_vect *ray_dir)
{
	if (!side)
	{
		if (ray_dir->x < 0)
			return (game->sprites->west);
		else
			return (game->sprites->east);
	}
	else
	{
		if (ray_dir->y < 0)
			return (game->sprites->north);
		else
			return (game->sprites->south);
	}
}

unsigned int	get_pixel_color(void *texture,
	int tex_x, int tex_y, int texture_width)
{
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		offset;

	data = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
	offset = (tex_y * size_line) + (tex_x * (bpp / 8));
	return (*(unsigned int *)(data + offset));
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
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
