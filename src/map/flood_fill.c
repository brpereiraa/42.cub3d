/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:55:10 by davioliv          #+#    #+#             */
/*   Updated: 2025/01/07 17:03:57 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	static int	player;

	if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
		player++;
	if (map[x][y] == '1')
		return (0);
	if (map[x][y] != '1' && map[x][y] != '0' && map[x][y] != ' ')
		return (1);
	map[x][y] = '1';
	flood_fill(map, x - 1, y);
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y - 1);
	flood_fill(map, x, y + 1);
	if (player > 1)
		return (2);
	return (0);
}

int	check_colors(char *input)
{
	int		i;
	int		j;
	char	**rgb;

	i = 0;
	j = 0;
	ft_strtrim(input, ' ');
	if (only_digits(input))
		return ("color code has more than digits");
	rgb = ft_split(input, ',');
	while (rgb[i++])
	{
		if ((ft_atoi(rgb[i]) > 255) || (ft_atoi(rgb[i] < 0)))
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
