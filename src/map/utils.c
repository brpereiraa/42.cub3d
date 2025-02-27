/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:22:58 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/27 23:50:59 by bruno            ###   ########.fr       */
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
	(void)i;
	if (col && (!ft_strcmp(col, "C") || !ft_strcmp(col, "F")))
	{
		if (!set_colors(game, col, end))
		{
			free(col);
			exit_project(game, "dwad");
		}
	}
}

void	check_commas(t_game *game, char *line, char *col)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ',' && line[i + 1] && line[i + 1] == ',')
		{
			free(col);
			clean_colors_trash(game, line, NULL, "Multiple commas\n");
		}
	}
	if (line[i - 1] == ',' || line[0] == ',')
	{
		free(col);
		clean_colors_trash(game, line, NULL, "Comma at the end/beggining\n");
	}
}

void	check_dup(t_game *game, char *col)
{
	char *error_message;

	if ((!ft_strcmp(col, "NO") && game->sprites->cnorth) ||
		(!ft_strcmp(col, "SO") && game->sprites->csouth) ||
		(!ft_strcmp(col, "WE") && game->sprites->cwest) ||
		(!ft_strcmp(col, "EA") && game->sprites->ceast) ||
		(!ft_strcmp(col, "F") && game->sprites->floor != 0) ||
		(!ft_strcmp(col, "C") && game->sprites->ceiling != 0))
	{
		if (!ft_strcmp(col, "NO"))
			error_message = "Duplicate NO texture\n";
		else if (!ft_strcmp(col, "SO"))
			error_message = "Duplicate SO texture\n";
		else if (!ft_strcmp(col, "WE"))
			error_message = "Duplicate WE texture\n";
		else if (!ft_strcmp(col, "EA"))
			error_message = "Duplicate EA texture\n";
		else if (!ft_strcmp(col, "F"))
			error_message = "Duplicate floor color\n";
		else
			error_message = "Duplicate ceiling color\n";
		free(col);
		exit_project(game, error_message);
	}
}