/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:12:35 by davioliv          #+#    #+#             */
/*   Updated: 2025/02/16 16:17:47 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	no_we_alloc(t_game *game, char *line, int i)
{
	if (!ft_strncmp(game->map[i], "NO", 2))
	{
		if (!game->sprites->cnorth)
			game->sprites->cnorth = \
				ft_strdup((line + 2) + skip_spaces(line + 2));
		return (1);
	}
	if (!ft_strncmp(game->map[i], "WE", 2))
	{
		if (!game->sprites->cwest)
			game->sprites->cwest = \
				ft_strdup((line + 2) + skip_spaces(line + 2));
		return (1);
	}
	return (0);
}

void	clean_colors_trash(t_game *game, char *line, char **rgb, char *msg)
{
	if (line)
		free(line);
	if (rgb)
		dp_cleaner(rgb);
	exit_project(game, msg);
}

int	check_newline(t_game *game, char **map, int i)
{
	if (game->map[i][0] == '\n')
	{
		dp_cleaner(map);
		return (1);
	}
	return (0);
}

char	**alloc_map(int lines, char *file, int fd)
{
	int		flag;
	int		i;
	char	**map;
	char	*str;

	i = 0;
	flag = 0;
	map = (char **)malloc(sizeof(char *) * (lines + 1));
	while (i < lines)
	{
		str = get_next_line(fd);
		map[i++] = str;
		if (ft_strnstr(map[i - 1], "01", ft_strlen(map[i - 1])))
			flag = 1;
	}
	get_next_line(-1);
	map[i] = NULL;
	if (flag == 0)
	{
		dp_cleaner(map);
		return (NULL);
	}
	return (map);
}

int	exit_key(t_game *game)
{
	clean_project(game);
	exit(0);
}
