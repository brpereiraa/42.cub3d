/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:54 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/08 19:05:36 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

// void	calc_steps(t_vect *ray_dir, t_vect *step, t_vect side_dist)
// {
// 	if (ray_dir->x < 0)
// 	{
// 		step->x = -1;
// 		side_dist->x = (game->player->pos_x - map->x) * delta_dist->x;
// 	}
// 	else
// 	{
// 		step->x = 1;
// 		side_dist->x = (map->x + 1.0 - game->player->pos_x) * delta_dist->x;
// 	}
// 	if (ray_dir->y < 0)
// 	{
// 		step->y = -1;
// 		side_dist->y = (game->player->pos_y - map->y) * delta_dist->y;
// 	}
// 	else
// 	{
// 		step->y = 1;
// 		side_dist->y = (map->y + 1.0 - game->player->pos_y) * delta_dist->y;
// 	}
// }

// void	calc_dist(t_vect *side_dist, t_vect *delta_dist, )
// {
// 	t_vect	*delta_dist;
	

// 	delta_dist = new_vect(fabs(1 / ray_dir->x), fabs(1 / ray_dir->y));

// 	while (1)
// 	{
// 		if (side_dist->x < side_dist->y)
// 		{
// 			side_dist->x += delta_dist->x;
// 			map->x += step->x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist->y += delta_dist->y;
// 			map->y += step->y;
// 			side = 1;
// 		}
// 		if (game->fmap[(int)map->y][(int)map->x] == '1')
// 			break;
// 	}
// }
