/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:08:00 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 17:56:05 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_init(t_game *game, char *file)
{
	game->map = map_read(file);
	if (!game->map)	
		return (0);
	int	i = -1;
	while(game->map[++i]){
		printf("%s", game->map[i]);
	}
	return (1);
}

char	**map_read(char *file)
{
	int	fd;
	int	lines;
	int	i;
	char	**map;

	i = 0;
	lines = map_lines(file);
	if (!lines)
		return (NULL);
	fd = open(file, O_RDONLY);
	map = (char **)malloc(sizeof(char *) * lines + 1);
	while(i < lines)
		map[i++] = get_next_line(fd);
	map[i] = NULL;
	return (map);
}

int	map_lines(char *file)
{
	int	fd;
	int	i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (close(fd), printf("Error while trying to open map.\n"), 0);
	i = 0;
	while(get_next_line(fd))
		i++;
	if (i == 0)
		return (close(fd), printf("Invalid map: Empty file for map.\n"), 0);
	close(fd);
	return (i);

}
