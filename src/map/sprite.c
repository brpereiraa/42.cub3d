/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:58:51 by bruno             #+#    #+#             */
/*   Updated: 2025/02/12 23:12:11 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	sprites_init(t_game *game)
{
	int		i;
	int		j;
	char	*line_form;

	i = -1;
	j = 0;
	while (game->map[++i])
	{
		if (game->map[i][0] == 10)
			continue ;
		line_form = ft_strtrim(game->map[i], "\n");
		if (!line_form || ft_strlen(line_form) <= 3)
		{
			free(line_form);
			exit_project(game, "Unable to trim newline");
		}
		if (check_if_wall(game->map[i]))
			if (set_sprite_walls(game, line_form, i))
				j++;
		if (set_colors(game, line_form, i))
			j++;
		free(line_form);
	}
	if (j != 6)
		exit_project(game, "Wrong number of sprite configurations\n");
}

int	color_init(t_game *game, char *line)
{
	char	**values;
	char	**rgb;
	int		rgb_i[3];
	int		i;

	values = ft_split(line, ' ');
	if (values[2] || !values[1])
		clean_colors_trash(game, line, values, "Invalid sprite information\n");
	rgb = ft_split(values[1], ',');
	i = 0;
	dp_cleaner(values);
	while (rgb[i])
		if (only_digits(rgb[i++]))
			clean_colors_trash(game, line, rgb, \
			"Color code has invalid characters\n");
	if (i != 3)
		clean_colors_trash(game, line, rgb, "Invalid sprite information\n");
	rgb_i[0] = ft_atoi(rgb[0]);
	rgb_i[1] = ft_atoi(rgb[1]);
	rgb_i[2] = ft_atoi(rgb[2]);
	dp_cleaner(rgb);
	if (check_rgb(rgb_i))
		clean_colors_trash(game, line, NULL, "Invalid color values\n");
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
	if (!ft_strncmp(line, "SO", 2) \
		|| !ft_strncmp(line, "EA", 2) \
		|| !ft_strncmp(line, "WE", 2) \
		|| !ft_strncmp(line, "NO", 2))
		return (1);
	return (0);
}

int	reach_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (map[++i])
	{
		if (ft_strnstr(map[i], "01", ft_strlen(map[i])))
			return (0);
		if (check_if_wall(map[i]))
			j++;
		if (!ft_strncmp(map[i], "F", 1) || !ft_strncmp(map[i], "C", 1))
			j++;
		if (j == 6)
			break ;
	}
	if (j != 6)
		return (0);
	while (map[i++][0] && map[i][0] == '\n')
		;
	return (i);
}
