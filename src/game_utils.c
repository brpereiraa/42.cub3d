/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:57:35 by davioliv          #+#    #+#             */
/*   Updated: 2025/02/11 02:16:17 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_invalid_chars(char **map)
{
	int	i;
	int	reach_map;
	int	j;

	i = -1;
	j = -1;
	reach_map = -1;
	while (!ft_strchr("01", map[++reach_map][0]))
		;
	while (map[reach_map + ++i])
	{
		j = -1;
		while (map[reach_map + i][++j])
		{
			if (map[reach_map + i][j] != '0' && map[reach_map + i][j] != '1' \
				&& map[reach_map + i][j] != 'N' && map[reach_map + i][j] != 'W' \
				&& map[reach_map + i][j] != 'E' && map[reach_map + i][j] != 'S' \
				&& map[reach_map + i][j] != ' ' \
				&& map[reach_map + i][j] != '\n')
				return (1);
		}
	}
	return (0);
}

char	**fmap_utils(t_game *game, int start)
{
	int	j;
	int	k;

	j = -1;
	while (game->map[start + ++j])
	{
		k = -1;
		while (game->map[start + j][++k])
		{
			if (game->map[start + j][k] == 'E' \
				|| game->map[start + j][k] == 'W' \
				|| game->map[start + j][k] == 'S' \
				|| game->map[start + j][k] == 'N')
			{
				game->player->pos_x = (double)k + 0.5;
				game->player->pos_y = (double)j + 0.5;
				player_fov(game, game->map[start + j][k]);
				return (&game->map[start]);
			}
		}
	}
	return (&game->map[start]);
}

void	draw_wall(t_game *game, int i, int j, int color)
{
	int	size;
	int	k;
	int	l;

	size = 10;
	k = -1;
	l = -1;
	while (++k < size)
	{
		l = -1;
		while (++l < size)
			pixel_put(game->data, i + l, j + k, color);
	}
}

int	set_sprite_walls(t_game *game, char *line, int i)
{
	if (check_sprite_syntax((line + 2) + skip_spaces(line + 2)))
	{
		free(line);
		exit_project(game, "Wrong sprite extensions\n");
	}
	if (!ft_strncmp(game->map[i], "SO", 2))
	{
		if (!game->sprites->csouth)
			game->sprites->csouth = ft_strdup((line + 2) + skip_spaces(line + 2));
		return (1);
	}
	if (!ft_strncmp(game->map[i], "EA", 2))
	{
		if (!game->sprites->ceast)
			game->sprites->ceast = ft_strdup((line + 2) + skip_spaces(line + 2));
		return (1);
	}
	if (!ft_strncmp(game->map[i], "NO", 2))
	{
		if (!game->sprites->cnorth)
			game->sprites->cnorth = ft_strdup((line + 2) + skip_spaces(line + 2));
		return (1);
	}
	if (!ft_strncmp(game->map[i], "WE", 2))
	{
		if (!game->sprites->cwest)
			game->sprites->cwest = ft_strdup((line + 2) + skip_spaces(line + 2));
		return (1);
	}
	return (0);
}

int	set_colors(t_game *game, char *line, int i)
{
	if (!ft_strncmp(game->map[i], "C", 1))
	{
		game->sprites->ceiling = color_init(game, line);
		return (1);
	}
	if (!ft_strncmp(game->map[i], "F", 1))
	{
		game->sprites->floor = color_init(game, line);
		return (1);
	}
	return (0);
}
