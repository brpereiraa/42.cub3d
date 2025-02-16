/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:06:47 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 22:59:13 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_extension(char *map)
{
	char	*file;

	file = ft_strchr(map, '.');
	if (file == NULL || !ft_strcmp(map, ".cub"))
		return (1);
	while (ft_strchr(file + 1, '.'))
		file = ft_strchr(file + 1, '.');
	if (ft_strcmp(file, ".cub"))
		return (1);
	return (0);
}

int	check_sprite_syntax(char *sprite)
{
	int		fd;
	char	*ext;
	char	*line;

	line = ft_substr(sprite, 0, ft_strlen(sprite) - 1);
	ext = ft_strchr(line, '.');
	while (ext && ft_strchr(ext + 1, '.'))
		ext = ft_strchr(ext + 1, '.');
	if (ext == NULL || ft_strcmp(ext, ".xpm"))
	{
		free (line);
		return (printf("Error\nInvalid extension\n"), 1);
	}
	fd = open(line, O_RDONLY);
	if (fd == -1)
	{
		free (line);
		return (printf("Error\nSprite: Non existent file\n"), 1);
	}
	free (line);
	close(fd);
	return (0);
}

int	check_rgb(int *color)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (color[i] > 255 || color[i] < 0)
			return (1);
	return (0);
}

int	only_digits(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] < '0' || input[i] > '9')
			return (1);
	return (0);
}
