/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:58:51 by bruno             #+#    #+#             */
/*   Updated: 2025/01/08 03:22:23 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	sprites_init(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[++i])
	{
		if (!ft_strncmp(game->map[i], "SO", 2))
			game->sprites->south = game->map[i];
		if (!ft_strncmp(game->map[i], "EA", 2))
			game->sprites->east = game->map[i];
		if (!ft_strncmp(game->map[i], "NO", 2))
			game->sprites->north = game->map[i];
		if (!ft_strncmp(game->map[i], "WE", 2))
			game->sprites->west = game->map[i];
		if (!ft_strncmp(game->map[i], "C", 1))
			game->sprites->ceiling = color_init(game, game->map[i]);
		if (!ft_strncmp(game->map[i], "F", 1))
			game->sprites->floor = color_init(game, game->map[i]);
	}
}

int color_init(t_game *game, char *line)
{
    char **values;
    char **rgb;
    int  rgb_i[3];

    printf("%s\n", line);
    values = ft_split(line, ' ');
    if(values[2] || !values[1])
        return (printf("Invalid sprite information\n"), 0);
    rgb = ft_split(values[1], ',');
    if(rgb[3] || !rgb[2])
        return (printf("Invalid sprite information\n"), 0);    
    rgb_i[0] = ft_atoi(rgb[0]);
    rgb_i[1] = ft_atoi(rgb[1]);
    rgb_i[2] = ft_atoi(rgb[2]);
    return (shift_color(rgb_i));
}

int	shift_color(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8
			| rgb[2]);
	return (color);
}