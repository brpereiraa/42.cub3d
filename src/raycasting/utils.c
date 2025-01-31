/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:46:54 by brpereir          #+#    #+#             */
/*   Updated: 2025/01/31 17:20:06 by bruno            ###   ########.fr       */
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

// void	calc_step_textures()