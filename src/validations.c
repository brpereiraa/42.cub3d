/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/10/09 20:08:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int color_validation(char *map)
{
	char	**str;
	int		i;
	int		j;

	i = -1;
	str = ft_split(map, ',');
	while(str[++i])
	{
		j = -1;
		while(str[i][++j])
			if(str[i][j] < '0' || str[i][j] > '9')
				return(printf("Invalid colors"), 1);
		if(ft_atoi(str[i]) < 0 || ft_atoi(str[i]) > 255)
			return(printf("Invalid colors"), 1);
	}
	return (0);
}

int char_validation(char *map)
{
	int	i;

	i = -1;
	if (map == NULL) 
	    return -1;
	while (map[++i])
		if (!ft_strchr(" 012NSEWAOFC\n", map[i]))
			return (1);
	return(0);
}

int sfile_validation(char *file)
{
	int			fd;
	char	*file1;
	
	file1 = ft_substr(file, 0, ft_strlen(file) - 1);
	free(file);
	fd = open(file1, O_RDONLY);
	if(fd == -1)
	{
		printf("'%s'\n", file1);
		close(fd);
		return (printf("Invalid sprite file"), 0);
	}
	close(fd);
	return (1);
}

int sprite_validation(char **map)
{
	int	i;
	char	**str;

	i = -1;
	while(++i < 7)
	{
		str = ft_split(map[i], 32);
		if (str[2])
			return(printf("Invalid map\n"), 1);
		if (char_validation(*str))
			return (printf("Invalid characters in textures\n"), 1);
		if (!ft_strcmp(*str, "EA") || !ft_strcmp(*str, "SO")
			|| !ft_strcmp(*str, "WE") || !ft_strcmp(*str, "NO"))
			sfile_validation(str[1]);
		else if (!ft_strcmp(*str, "C") || !ft_strcmp(*str, "F"))
			if (color_validation(str[1]))
				return (1);
		// else
		// 	return(printf("Wrong information on map textures\n"), 1); 
	}

	return (0);
}

int file_validation(char *map)
{
    char *file;

    file = ft_strchr(map, '.');
    if (file == NULL || !ft_strcmp(map, ".cub"))
		return (printf("Invalid file name\n"), 0);
	while (ft_strchr(file + 1, '.'))
		file = ft_strchr(file + 1, '.');
	if(ft_strcmp(file, ".cub"))
		return (printf("File name doesn't end with .cub\n"), 0);
    return (1);
}

int map_validation(char *map)
{
	int		fd;
	int		n_line;
	int		i;
	char	**lines;
	char	*str;

	n_line = 0;
	fd = open(map, O_RDONLY);
	i = -1;
	while((str = get_next_line(fd)))
		n_line++;
	close(fd);
	if(n_line == 0)
		return (printf("Invalid number of lines"), 0);
	fd = open(map, O_RDONLY);
	lines = (char **)malloc(sizeof(char *) * n_line);	
	while(++i < n_line)
		lines[i] = get_next_line(fd);
	i = -1;
	if(!sprite_validation(lines))
		return (0);
	return (1);
}