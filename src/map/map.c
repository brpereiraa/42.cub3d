/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:08:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 00:53:24 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	map_init(t_game *game, char *file)
{
	if (check_extension(file))
		exit_project(game, "File has wrong extension\nInvalid map\n");
	game->map = map_read(file);
	if (!game->map)
		exit_project(game, "Couldn't create map\nInvalid map\n");
	check_flood_fill(game);
	if (!game->player)
		exit_project(game, "Couldn't alloc player struct\n");
	game->player->perp = (t_vect *)malloc(sizeof(t_vect));
	game->fmap = fmap_read(game);
	if (!game->fmap)
		exit_project(game, "Error reading map.\n");
	if (!game->sprites)
		exit_project(game, "Couldn't alloc sprites\n");
	sprites_init(game);
}

char	**map_read(char *file)
{
	char	**map;
	int		fd;
	int		lines;

	fd = open(file, O_RDONLY);
	lines = map_lines(file);
	if (!lines)
		return (NULL);
	map = alloc_map(lines, file, fd);
	return (map);
}

int	map_lines(char *file)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		i++;
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	return (i);
}

char	**fmap_read(t_game *game)
{
	int	i;

	i = -1;
	game->fv = (t_vect *)malloc(sizeof(t_vect));
	game->fv->x = 1;
	game->fv->y = 1;
	i = reach_map(game->map);
	return (fmap_utils(game, i));
}

void	player_fov(t_game *game, char c)
{
	if (c == 'E')
		game->player->angle = new_vect(1, 0);
	if (c == 'W')
		game->player->angle = new_vect(-1, 0);
	if (c == 'S')
		game->player->angle = new_vect(0, 1);
	if (c == 'N')
		game->player->angle = new_vect(0, -1);
	perp_vect(game->player->angle, game->player->perp);
}
