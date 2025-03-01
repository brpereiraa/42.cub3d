/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:57:35 by davioliv          #+#    #+#             */
/*   Updated: 2025/03/01 23:51:28 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_invalid_chars(char **map)
{
	int	i;
	int	reach;
	int	j;

	i = -1;
	j = -1;
	reach = reach_map(map);
	if (!reach)
		return (1);
	while (map[reach + ++i])
	{
		j = -1;
		while (map[reach + i][++j])
		{
			if (map[reach + i][j] != '0' && map[reach + i][j] != '1' \
				&& map[reach + i][j] != 'N' && map[reach + i][j] != 'W' \
				&& map[reach + i][j] != 'E' && map[reach + i][j] != 'S' \
				&& !ft_isspace(map[reach + i][j]) \
				&& map[reach + i][j] != '\n')
			{
				return (printf("Error\nInvalid characters found\n"), 1);
			}
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

int	set_sprite_walls(t_game *game, char *col, char *line)
{
	char	*fline;

	fline = ft_strpbrk_skip(line, " \t");
	if (fline[0] == '\n')
		clean_colors_trash(game, col, NULL, "Invalid information");
	if (strncmp(fline, "EA", 2) == 0 || strncmp(fline, "NO", 2) == 0 ||
		strncmp(fline, "SO", 2) == 0 || strncmp(fline, "WE", 2) == 0)
		fline = ft_strpbrk_skip(fline + 2, " \t");
	if (check_sprite_syntax(fline))
	{
		free (col);
		exit_project(game, NULL);
	}
	if (!ft_strcmp(col, "SO"))
		game->sprites->csouth = ft_substr(fline, 0, ft_strlen(fline) - 1);
	else if (!ft_strcmp(col, "NO"))
		game->sprites->cnorth = ft_substr(fline, 0, ft_strlen(fline) - 1);
	else if (!ft_strcmp(col, "EA"))
		game->sprites->ceast = ft_substr(fline, 0, ft_strlen(fline) - 1);
	else if (!ft_strcmp(col, "WE"))
		game->sprites->cwest = ft_substr(fline, 0, ft_strlen(fline) - 1);
	return (0);
}

int	set_colors(t_game *game, char *col, char *line)
{
	char	*end;

	end = ft_strpbrk_skip(line, " \t");
	end = ft_substr(end, 0, ft_strlen(end) - 1);
	if (!ft_strcmp(col, "C"))
	{
		game->sprites->ceiling = color_init(game, end, col);
		return (1);
	}
	if (!ft_strcmp(col, "F"))
	{
		game->sprites->floor = color_init(game, end, col);
		return (1);
	}
	return (0);
}
