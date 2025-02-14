/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:55:10 by davioliv          #+#    #+#             */
/*   Updated: 2025/02/14 15:42:20 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	flood_fill(int x, int y, t_game *game)
{
	if (x < 0 || x >= game->max_y || y < 0 || y >= game->max_x \
			|| !game->flood_map[x][y])
	{
		dp_cleaner(game->flood_map);
		exit_project(game, "Map is open\n");
	}
	if (game->flood_map[x][y] == '1')
		return (1);
	else if (game->flood_map[x][y] != '0' && game->flood_map[x][y] != 'N' \
			&& game->flood_map[x][y] != 'S' && game->flood_map[x][y] != 'E' \
			&& game->flood_map[x][y] != 'W')
	{
		dp_cleaner(game->flood_map);
		exit_project(game, "Map is open\n");
	}
	game->flood_map[x][y] = '1';
	flood_fill(x - 1, y, game);
	flood_fill(x + 1, y, game);
	flood_fill(x, y - 1, game);
	flood_fill(x, y + 1, game);
	return (0);
}

int	check_flood_fill(t_game *game)
{
	int	i;

	i = -1;
	if (check_invalid_chars(game->map))
		exit_project(game, NULL);
	game->flood_map = create_flood_map(game);
	if (!game->flood_map)
		exit_project(game, "Couldn't alloc flood_map\n");
	flood_fill(game->start_y, game->start_x, game);
	dp_cleaner(game->flood_map);
	return (1);
}

char	**create_flood_map(t_game *game)
{
	char	**only_map;
	int		i;
	int		reach;

	reach = reach_map(game->map);
	i = -1;
	while (game->map[reach + ++i])
		;
	only_map = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (game->map[reach + ++i])
	{
		if (check_newline(game, only_map, reach + i))
			return (NULL);
		only_map[i] = ft_strdup(game->map[reach + i]);
	}
	only_map[i] = NULL;
	if (flood_map_utils(reach, game))
	{
		dp_cleaner(only_map);
		exit_project(game, "Wrong number of players\n");
	}
	return (only_map);
}

int	flood_map_utils(int start, t_game *game)
{
	int	i;
	int	j;
	int	check_num_p;
	int	max_x;

	i = -1;
	check_num_p = 0;
	max_x = ft_strlen(game->map[start]);
	while (game->map[start + ++i])
	{
		if (ft_strlen(game->map[start + i]) > max_x)
			max_x = ft_strlen(game->map[start + i]);
		j = -1;
		while (game->map[start + i][++j])
		{
			if (!check_player(game->map[start + i][j], game, i, j))
				check_num_p++;
		}
	}
	if (check_num_p != 1)
		return (1);
	game->max_x = max_x;
	game->max_y = i;
	return (0);
}

int	check_player(char c, t_game *game, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->start_x = j;
		game->start_y = i;
		return (0);
	}
	return (1);
}
