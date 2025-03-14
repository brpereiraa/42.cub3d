/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:04:59 by davioliv          #+#    #+#             */
/*   Updated: 2025/03/01 23:44:57 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_mlx_init(t_game *game)
{
	int	size;

	size = 50;
	game->data->mlx = mlx_init();
	game->data->win = mlx_new_window(game->data->mlx, WIDTH, HEIGHT, "Cub3D");
	game->sprites->south = mlx_xpm_file_to_image \
		(game->data->mlx, game->sprites->csouth, &size, &size);
	game->sprites->north = mlx_xpm_file_to_image \
		(game->data->mlx, game->sprites->cnorth, &size, &size);
	game->sprites->west = mlx_xpm_file_to_image \
		(game->data->mlx, game->sprites->cwest, &size, &size);
	game->sprites->east = mlx_xpm_file_to_image \
		(game->data->mlx, game->sprites->ceast, &size, &size);
	if (!game->sprites->south || !game->sprites->north \
		|| !game->sprites->east || !game->sprites->west)
		exit_project(game, "Invalid sprite file\n");
	minimap_loop(game);
	return (1);
}

void	minimap_loop(t_game *game)
{
	t_data	*data;

	data = game->data;
	mlx_hook (data->win, 2, 1L << 0, key_handler, game);
	mlx_hook (data->win, 17, 1L << 17, exit_key, game);
	mlx_loop_hook(data->mlx, ft_render, game);
	mlx_loop (data->mlx);
	return ;
}

void	mlx_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

void	destroy_images(t_game *game)
{
	mlx_destroy_image(game->data->mlx, game->data->img);
}
