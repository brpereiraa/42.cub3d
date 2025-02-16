/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:58:51 by bruno             #+#    #+#             */
/*   Updated: 2025/02/14 18:39:55 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	sprites_init(t_game *game)
{
	int		i;
	int		j;
	char	*end;
	char	*col;

	i = -1;
	j = 0;
	col = NULL;
	while (game->map[++i])
	{
		col = game->map[i];
		if (ft_strchr(" \t", game->map[i][0]))
			col = ft_strpbrk_skip(game->map[i], " \t");
		end = ft_strpbrk(col, " \t");
		if (!end)
			continue ;
		col = ft_substr(col, 0, end - col);
		if (col && check_if_wall(col))
		{
			if (set_sprite_walls(game, col, game->map[i]))
			{
				free(col);
				exit_project(game, NULL);
			}
		}
		if (col && (!ft_strcmp(col, "C") || !ft_strcmp(col, "F")))
		{
			if (!set_colors(game, col, end))
			{
				free(col);
				exit_project(game, "dwad");
			}
		}
		free(col);
		j++;
	}
}

int	color_init(t_game *game, char *line, char *col)
{
	char	**rgb;
	int		rgb_i[3];
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
	rgb = ft_split(line, ',');
	i = 0;
	while (rgb[i])
		if (only_digits(rgb[i++]))
			clean_colors_trash(game, line, rgb, "Color: Invalid characters\n");
	if (i != 3)
		clean_colors_trash(game, line, rgb, "Invalid sprite information\n");
	rgb_i[0] = ft_atoi(rgb[0]);
	rgb_i[1] = ft_atoi(rgb[1]);
	rgb_i[2] = ft_atoi(rgb[2]);
	dp_cleaner(rgb);
	if (check_rgb(rgb_i))
		clean_colors_trash(game, line, NULL, "Invalid color values\n");
	free (line);
	return (shift_color(rgb_i));
}

int	shift_color(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8
			| rgb[2]);
	return (color);
}

int	check_if_wall(char *line)
{
	if (!ft_strcmp(line, "SO") \
		|| !ft_strcmp(line, "EA") \
		|| !ft_strcmp(line, "WE") \
		|| !ft_strcmp(line, "NO"))
		return (1);
	return (0);
}

int	reach_map(char **map)
{
	int		i;
	int		j;
	char	*end;
	char	*col;

	i = -1;
	j = 0;
	while (map[++i])
	{
		col = map[i];
		if (ft_strchr(" \t", col[0]))
			col = ft_strpbrk_skip(col, " \t");
		end = ft_strpbrk(col, " \t");
		if (!end)
			continue ;
		col = ft_substr(col, 0, end - col);
		if (check_if_wall(col))
			j++;
		else if (!ft_strcmp(col, "F") || !ft_strcmp(col, "C"))
			j++;
		else if (*col && ft_isalpha(col[0]))
			return (free(col), printf("Error: Not all \
			information before map\n"), 0);
		if (j == 6)
			break ;
		free (col);
	}
	if (j != 6)
		return (printf("Missing information\n"), 0);
	while (map[i] && map[i++] && map[i][0] == '\n')
		;
	return (i);
}
