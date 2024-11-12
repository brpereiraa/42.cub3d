/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:08:00 by marvin            #+#    #+#             */
/*   Updated: 2024/11/12 15:41:28 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_init(t_game *game, char *file)
{
	if(check_extension(file))
		return (0);
	game->map = map_read(file);
	if (!game->map)	
		return (0);
	game->player = (t_player *)malloc(sizeof(t_player));
	game->fmap = fmap_read(game);
	if (!game->fmap)
		return (printf("Error reading map.\n"),0);
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

void	sprite_info(t_game *game)
{
	int	i;

	i = 0;
	game->sprites = (t_sprites *)malloc(sizeof(t_sprites));
	while(game->map[++i])
	{
		if (!ft_strncmp(game->map[i], "SO", 2))
			game->sprites->south = game->map[i];
		if (!ft_strncmp(game->map[i], "EA", 2))
			game->sprites->east = game->map[i];
		if (!ft_strncmp(game->map[i], "NO", 2))
			game->sprites->north = game->map[i];
		if (!ft_strncmp(game->map[i], "WE", 2))
			game->sprites->west = game->map[i];
		if (!ft_strncmp(game->map[i], "C", 1))
			game->sprites->ceiling = game->map[i];
		if (!ft_strncmp(game->map[i], "F", 1))
			game->sprites->floor = game->map[i];
	}
}

char	**fmap_read(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	while(!ft_strchr("01", game->map[++i][0]))
		;
	while(game->map[i + ++j])
	{
		k = -1;
		while(game->map[i + j][++k])
			if (game->map[i+j][k] == 'E')
			{
				printf("JUan\n");
				game->player->pos_x = (double)k;
				game->player->pos_y = (double)j;
				return (&game->map[i]);
			}
	}
	return (&game->map[i]);
}
