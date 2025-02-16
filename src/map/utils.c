/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:22:58 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/16 16:30:37 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_rgb_val(t_game *game, char *line, char *col, char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (only_digits(rgb[i++]))
		{
			free (col);
			clean_colors_trash(game, line, rgb, "Color: Invalid characters\n");
		}
	}
	if (i != 3)
	{
		free (col);
		clean_colors_trash(game, line, rgb, "Invalid sprite information\n");
	}
}

void	handle_walls(t_game *game, char *col, int i)
{
	if (col && check_if_wall(col))
	{
		if (set_sprite_walls(game, col, game->map[i]))
		{
			free(col);
			exit_project(game, NULL);
		}
	}
}

void	handle_colors(t_game *game, char *col, char *end, int i)
{
	if (col && (!ft_strcmp(col, "C") || !ft_strcmp(col, "F")))
	{
		if (!set_colors(game, col, end))
		{
			free(col);
			exit_project(game, "dwad");
		}
	}
}
