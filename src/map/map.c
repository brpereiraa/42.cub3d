/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:08:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/30 22:55:39 by davioliv         ###   ########.fr       */
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
	check_flood_fill(game);
	game->player = (t_player *)malloc(sizeof(t_player));
	if (!game->player)
		exit_project(game, "Couldn't alloc player struct\n");
	game->player->perp = (t_vect *)malloc(sizeof(t_vect));
	game->fmap = fmap_read(game);
	if (!game->fmap)
		exit_project(game, "Error reading map.\n");
	game->sprites = (t_sprites *)malloc(sizeof(t_sprites));
	if (!game->sprites)
		exit_project(game, "Couldn't alloc sprites\n");
	game->data = (t_data *)malloc(sizeof(t_data));
	start_sprites(game);
	sprites_init(game);
}

char	**map_read(char *file)
{
	int		fd;
	int		lines;
	int		i;
	char	**map;
	int		flag;

	i = 0;
	flag = 0;
	lines = map_lines(file);
	if (!lines)
		return (NULL);
	fd = open(file, O_RDONLY);
	map = (char **)malloc(sizeof(char *) * (lines + 1));
	while (i < lines)
	{
		map[i++] = ft_strtrim(get_next_line(fd), " ");
		if (ft_strnstr(map[i - 1], "01", ft_strlen(map[i - 1])))
			flag = 1;
	}
	map[i] = NULL;
	if (flag == 0)
		return (NULL);
	return (map);
}

int	map_lines(char *file)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (close(fd), printf("Error while trying to open map.\n"), 0);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		i++;
		str = get_next_line(fd);
	}
	free(str);
	if (i == 0)
		return (close(fd), printf("Invalid map: Empty file for map.\n"), 0);
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
	while (!ft_strchr("01", game->map[++i][0]))
		;
	return (fmap_utils(game, i));
}

void	player_fov(t_game *game, char c)
{
	if (c == 'E')
		game->player->angle = new_vect(-1, 0);
	if (c == 'W')
		game->player->angle = new_vect(1, 0);
	if (c == 'S')
		game->player->angle = new_vect(0, 1);
	if (c == 'N')
		game->player->angle = new_vect(0, -1);
	perp_vect(game->player->angle, game->player->perp);
}
