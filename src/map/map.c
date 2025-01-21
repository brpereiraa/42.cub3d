/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:08:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/20 18:32:23 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_init(t_game *game, char *file)
{
	if (check_extension(file))
		exit_project(game, "File has wrong extension\nInvalid map\n");
	game->map = map_read(file);
	if (!game->map)
		exit_project(game, "Couldn't create map\nInvalid map\n");
	if (!check_flood_fill(game))
		exit_project(game, "Map not closed\nInvalid map\n");
	game->player = (t_player *)malloc(sizeof(t_player));
	if (!game->player)
		exit_project(game, "Couldn't alloc player struct\n");
	game->fmap = fmap_read(game);
	if (!game->fmap)
		exit_project(game, "Error reading map.\n");
	game->sprites = (t_sprites *)malloc(sizeof(t_sprites));
	if (!game->sprites)
		exit_project(game, "Couldn't alloc sprites\n");
	sprites_init(game);
}

char	**map_read(char *file)
{
	int		fd;
	int		lines;
	int		i;
	char	**map;

	i = 0;
	lines = map_lines(file);
	if (!lines)
		return (NULL);
	fd = open(file, O_RDONLY);
	map = (char **)malloc(sizeof(char *) * (lines + 1));
	while (i < lines)
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
	while (get_next_line(fd))
		i++;
	if (i == 0)
		return (close(fd), printf("Invalid map: Empty file for map.\n"), 0);
	close(fd);
	return (i);
}

char	**fmap_read(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	game->fv = (t_vect *)malloc(sizeof(t_vect));
	game->fv->x = 1;
	game->fv->y = 1;
	while (!ft_strchr("01", game->map[++i][0]))
		;
	while (game->map[i + ++j])
	{
		k = -1;
		while (game->map[i + j][++k])
		{
			if (game->map[i + j][k] == 'E' || game->map[i + j][k] == 'W' || game->map[i + j][k] == 'S' || game->map[i + j][k] == 'N')
			{
				game->player->pos_x = (double)k + 0.5;
				game->player->pos_y = (double)j + 0.5;
				player_fov(game, game->map[i + j][k]);				
				return (&game->map[i]);
			}
		}
	}
	return (&game->map[i]);
}

void	player_fov(t_game *game, char c)
{
	if (c == 'E')
		game->player->angle = *new_vect(-1, 0);
	if (c == 'W')
		game->player->angle = *new_vect(1, 0);
	if (c == 'S')
		game->player->angle = *new_vect(0, 1);
	if (c == 'N')
		game->player->angle = *new_vect(0, -1);
	perp_vect(&game->player->angle, &game->player->perp);
}
