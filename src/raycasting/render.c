/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:12:13 by brpereir          #+#    #+#             */
/*   Updated: 2024/11/22 20:37:55 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void create_image(t_game *game)
{
	t_data *data;

	data = game->data;
	data->img = mlx_new_image(data->mlx, 500, 700);
	data->addr = mlx_get_data_addr(data->img, &data->bits, &data->len, &data->endian);
}

int ft_render(t_game *game)
{
	create_image(game);
	// start_window(game);
	ft_raycasting(game);
	mmap_init(game);
	destroy_images(game);
	
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
	if (!data->win)
		return (printf("Error starting img.\n"), 0);
	return (1);
}