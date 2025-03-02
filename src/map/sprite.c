/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:58:51 by bruno             #+#    #+#             */
/*   Updated: 2025/03/02 17:13:31 by brpereir         ###   ########.fr       */
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
		check_dup(game, col);
		handle_walls(game, col, end);
		handle_colors(game, col, end, i);
		free(col);
		j++;
	}
}

int	color_init(t_game *game, char *line, char *col)
{
	char	**rgb;
	int		rgb_i[3];
	int		i;

	check_commas(game, line, col);
	rgb = ft_split(line, ',');
	i = -1;
	check_rgb_val(game, line, col, rgb);
	while (++i < 3)
		rgb_i[i] = ft_atoi(rgb[i]);
	dp_cleaner(rgb);
	if (check_rgb(rgb_i))
	{
		free (col);
		clean_colors_trash(game, line, NULL, "Invalid color values\n");
	}
	return (free (line), shift_color(rgb_i));
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
		if (!check_data(&j, col, end))
			return (0);
		if (j == 6)
			break ;
	}
	if (j != 6)
		return (printf("Error\nMissing information\n"), 0);
	while (map[i] && map[i++] && map[i][0] == '\n')
		;
	return (i);
}
