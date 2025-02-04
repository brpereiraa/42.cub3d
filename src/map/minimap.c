/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:34:55 by davioliv          #+#    #+#             */
/*   Updated: 2025/02/04 16:35:05 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_fov(t_game *game);

int	mmap_init(t_game *game)
{
	render_images(game);
	return (1);
}

void	put_image_to_window(t_game *game, int i, int j)
{
	int	size;

	size = 50;
	if (game->fmap[i][j] == '1')
		draw_wall(game, j * 10, i * 10, BLACK);
	if (game->fmap[i][j] == '0' || game->fmap[i][j] == 'W' \
		|| game->fmap[i][j] == 'E' || game->fmap[i][j] == 'S' \
		|| game->fmap[i][j] == 'N' )
		draw_wall(game, j * 10, i * 10, GREY);
	return ;
}

void	render_images(t_game *game)
{
	t_data	*data;
	int		i;
	int		j;

	i = -1;
	data = game->data;
	while (game->fmap[++i])
	{
		j = -1;
		while (game->fmap[i][++j])
			put_image_to_window(game, i, j);
	}
	ft_fov(game);
	mlx_put_image_to_window(data->mlx, data->win, game->data->img, 0, 0);
	return ;
}

void	cast_rays(t_game *game, t_vect *perp)
{
	t_vect	vect;
	double	step_size;
	double	next_x;
	double	next_y;

	step_size = 0.01;
	vect = *new_vect(game->player->pos_x, game->player->pos_y);
	while (1)
	{
		next_x = vect.x + game->player->angle.x \
			* step_size + perp->x * step_size;
		next_y = vect.y + game->player->angle.y \
			* step_size + perp->y * step_size;
		if (game->fmap[(int)next_y][(int)next_x] == '1' ||
			game->fmap[(int)(next_y + 0.1)][(int)next_x] == '1' ||
			game->fmap[(int)next_y][(int)(next_x + 0.1)] == '1' ||
			game->fmap[(int)(next_y - 0.1)][(int)next_x] == '1' ||
			game->fmap[(int)next_y][(int)(next_x - 0.1)] == '1')
			break ;
		vect.x = next_x;
		vect.y = next_y;
		pixel_put(game->data, vect.x * 10, vect.y * 10, WHITE);
		step_size += 0.0001;
	}
}

int	ft_fov(t_game *game)
{
	int		x;
	int		y;
	double	t;
	t_vect	ray_dir;

	x = (game->player->pos_x * 60);
	y = (game->player->pos_y * 60);
	t = 0;
	while (t <= 1)
	{
		ray_dir.x = t * game->player->perp.x;
		ray_dir.y = t * game->player->perp.y;
		cast_rays(game, &ray_dir);
		ray_dir.x = t * -game->player->perp.x;
		ray_dir.y = t * -game->player->perp.y;
		cast_rays(game, &ray_dir);
		t += 0.001;
	}
	mlx_put_image_to_window(game->data->mlx, \
			game->data->win, game->data->img, 0, 0);
	return (1);
}
