/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:06:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/28 21:43:27 by davioliv         ###   ########.fr       */
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

	ext = sprite + 1;
	ext = ft_strchr(ext, '.');
	if (ext == NULL || ft_strcmp(ext, ".xpm") != 0)
		return (ft_printf("Wrong sprite extensions\n"), 1);
	fd = open(sprite, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Unable to open sprite file\n"), 1);
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
