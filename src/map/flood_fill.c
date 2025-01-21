/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:55:10 by davioliv          #+#    #+#             */
/*   Updated: 2025/01/20 18:40:11 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	flood_fill(int x, int y, char **map, t_game *game)
{
	if (x < 0 || x >= game->max_y || y < 0 || y >= game->max_x)
		return (1);
	if (map[x][y] == '1')
		return (0);
	else if (map[x][y] != '0' && map[x][y] != 'N' \
			&& map[x][y] != 'S' && map[x][y] != 'E' && map[x][y] != 'W')
		return (1);
	map[x][y] = '1';
	flood_fill(x - 1, y, map, game);
	flood_fill(x + 1, y, map, game);
	flood_fill(x, y - 1, map, game);
	flood_fill(x, y + 1, map, game);
	return (0);
}

/*int	check_colors(char *input)
{
	int		i;
	int		j;
	char	**rgb;

	i = 0;
	j = 0;
	ft_strtrim(input, " ");
	if (only_digits(input))
		return ("color code has more than digits");
	rgb = ft_split(input, ',');
	while (rgb[i++])
	{
		if ((ft_atoi(rgb[i]) > 255) || (ft_atoi(rgb[i]) < 0))
			return ("error color");
	}
}

int	only_digits(char *input)
{
	int	i;

	i = 0;
	while (input[i++])
	{
		if (input[i] <= '0' || input[i] >= '9')
			return (1);
	}
	return (0);
}
*/
int	check_flood_fill(t_game *game)
{
	char	**flood_map;

	flood_map = create_flood_map(game);
	if (flood_fill(game->start_y, game->start_x, flood_map, game))
	{
		free(flood_map);
		return (printf("Map is open\n"), 0);
	}
	free(flood_map);
	return (1);
}

char	**create_flood_map(t_game *game)
{
	char	**only_map;
	int	i;
	int	reach_map;

	reach_map = -1;
	while (!ft_strchr("01", game->map[++reach_map][0]))
		;
	i = -1;
	while (game->map[reach_map + ++i])
		;
	only_map = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (game->map[reach_map + i])
		only_map[i] = game->map[reach_map + ++i];
	only_map[i] = NULL;
	flood_map_utils(reach_map, game);
	return (only_map);
}

void	flood_map_utils(int start, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[start + ++i])
	{
		j = -1;
		while (game->map[start + i][++j])
		{
			if (game->map[start + i][j] == 'N' || game->map[start + i][j] == 'S' \
					|| game->map[start + i][j] == 'E' || game->map[start + i][j] == 'W')
			{
				game->start_x = j;
				game->start_y = i;
			}
		}
	}
	game->max_x = j - 1;
	game->max_y = i - 1;
}
