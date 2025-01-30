/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:57:35 by davioliv          #+#    #+#             */
/*   Updated: 2025/01/28 21:52:05 by davioliv         ###   ########.fr       */
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
				&& map[reach_map + i][j] != ' ' && map[reach_map + i][j] != '\n')
				return (1);
		}
	}
	return (0);
}
