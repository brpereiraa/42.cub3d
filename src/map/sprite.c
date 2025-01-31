/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:58:51 by bruno             #+#    #+#             */
/*   Updated: 2025/01/31 18:08:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sprites_init(t_game *game)
{
	int		i;
	int		j;
	char		*line_form;

	i = -1;	
	j = 0;
	line_form = NULL;
	while (game->map[++i])
	{
		line_form = ft_strtrim(game->map[i], "\n");
		if (!line_form)
		{
			free(line_form);
			exit_project(game, "Unable to trim newline");
		}
		if (!ft_strncmp(game->map[i], "SO", 2))
		{
			if (check_sprite_syntax((line_form + 2) + skip_spaces(line_form + 2)))
				exit_project(game, NULL);
			game->sprites->south = (line_form + 2) + skip_spaces(line_form + 2);
			j++;
		}
		if (!ft_strncmp(game->map[i], "EA", 2))
		{
			if (check_sprite_syntax((line_form + 2) + skip_spaces(line_form + 2)))
				exit_project(game, NULL);
			game->sprites->east = (line_form + 2) + skip_spaces(line_form + 2);
			j++;
		}
		if (!ft_strncmp(game->map[i], "NO", 2))
		{
			if (check_sprite_syntax((line_form + 2) + skip_spaces(line_form + 2)))
				exit_project(game, NULL);
			game->sprites->north = (line_form + 2) + skip_spaces(line_form + 2);
			j++;
		}
		if (!ft_strncmp(game->map[i], "WE", 2))
		{
			if (check_sprite_syntax((line_form + 2) + skip_spaces(line_form + 2)))
				exit_project(game, NULL);
			game->sprites->west = (line_form + 2) + skip_spaces(line_form + 2);
			j++;
		}
		if (!ft_strncmp(game->map[i], "C", 1))
		{
			game->sprites->ceiling = color_init(game, line_form);
			j++;
		}
		if (!ft_strncmp(game->map[i], "F", 1))
		{
			game->sprites->floor = color_init(game, line_form);
			j++;
		}
	}
	if (j != 6)
		exit_project(game, "Wrong number of sprite configurations\n");
	free(line_form);
}

int	color_init(t_game *game, char *line)
{
	char	**values;
	char	**rgb;
	int		rgb_i[3];
	int		i;

	values = ft_split(line, ' ');
	if (values[2] || !values[1])
		exit_project(game, "Invalid sprite information\n");
	rgb = ft_split(values[1], ',');
	i = 0;
	while (rgb[i])
		if (only_digits(rgb[i++]))
			exit_project(game, "Color code has invalid characters\n");
	if (i != 3)
		exit_project(game, "Invalid sprite information\n");
	dp_cleaner(values);
	rgb_i[0] = ft_atoi(rgb[0]);
	rgb_i[1] = ft_atoi(rgb[1]);
	rgb_i[2] = ft_atoi(rgb[2]);
	dp_cleaner(rgb);
	free(line);
	if (check_rgb(rgb_i))
		exit_project(game, "Invalid color values\n");
	return (shift_color(rgb_i));
}

int	shift_color(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8
			| rgb[2]);
	return (color);
}
