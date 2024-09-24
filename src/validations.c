/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/09/24 17:36:54 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int char_validation(char *map)
{
	int	i;

	i = -1;
	if (map == NULL) 
	    return -1;
	while(map[++i])
		if(!ft_strchr(" 012NSEWAOFC\n", map[i]))
			return (1);
	return(0);
}

void sfile_validation(char *file)
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
		print_error("Invalid sprite file", 0);
	}
	close(fd);
}

int sprite_validation(char **map)
{
	int	i;
	char	**str;

	i = -1;
	while(++i < 7)
	{
		str = ft_split(map[i], 32);
		if(str[2])
			print_error("Invalid map", 0);
		if(char_validation(*str))
			return (1);
		if(!ft_strcmp(*str, "EA") || !ft_strcmp(*str, "SO") 
			|| !ft_strcmp(*str, "WE") || !ft_strcmp(*str, "NO"))
			sfile_validation(str[1]);
	}

	return (0);
}

int file_validation(char *map)
{
    char *file;

    file = ft_strchr(map, '.');
    if (file == NULL || !ft_strcmp(map, ".cub"))
		return 1;
	while (ft_strchr(file + 1, '.'))
		file = ft_strchr(file + 1, '.');
	if(ft_strcmp(file, ".cub"))
		return (1);
    return (0);
}

void map_validation(char *map)
{
	int		fd;
	int		n_line;
	int		i;
	char	**lines;
	char	*str;

	n_line = 0;
	fd = open(map, O_RDONLY);
	while((str = get_next_line(fd)))
		n_line++;
	close(fd);
	if(n_line == 0)
		print_error("Invalid number of lines", 0);
	fd = open(map, O_RDONLY);
	i = -1;
	lines = (char **)malloc(sizeof(char *) * n_line);	
	while(++i < n_line)
		lines[i] = get_next_line(fd);
	i = -1;
	if(sprite_validation(lines))
		print_error("Invalid characters", 0);
	
}