/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:12:13 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/16 16:49:07 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_image(t_game *game)
{
	t_data	*data;

	data = game->data;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr \
		(data->img, &data->bits, &data->len, &data->endian);
}

int	ft_render(t_game *game)
{
	create_image(game);
	start_window(game);
	ft_raycasting(game);
	mmap_init(game);
	mlx_destroy_image(game->data->mlx, game->data->img);
	return (0);
}

int	start_window(t_game *game)
{
	t_data	*data;

	data = game->data;
	if (!data->mlx)
		return (printf("Error starting mlx.\n"), 0);
	if (!data->win)
		return (printf("Error starting win.\n"), 0);
	if (!data->img)
		return (printf("Error starting img.\n"), 0);
	return (1);
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
