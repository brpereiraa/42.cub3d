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

int	flood_fill(int x, int y, t_game *game)
{
	int	i = 0;

/*	while (game->flood_map[i])
		printf("%s", game->flood_map[i++]);
	printf("\n\n");*/
	if (x < 0 || x >= game->max_y || y < 0 || y >= game->max_x)
	{
		dp_cleaner(game->flood_map);
		exit_project(game, "Map is open\n");
	}
	if (game->flood_map[x][y] == '1')
		return (0);
	else if (game->flood_map[x][y] != '0' && game->flood_map[x][y] != 'N' \
			&& game->flood_map[x][y] != 'S' && game->flood_map[x][y] != 'E' && game->flood_map[x][y] != 'W')
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
	game->flood_map = create_flood_map(game);
	flood_fill(game->start_y, game->start_x, game);
	dp_cleaner(game->flood_map);
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
	while (game->map[reach_map + ++i])
		only_map[i] = ft_strdup(game->map[reach_map + i]);
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
	game->max_x = j;
	game->max_y = i;
	printf("%d %d\n", game->max_y, game->max_x);
}
