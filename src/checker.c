/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:06:47 by marvin            #+#    #+#             */
/*   Updated: 2024/10/03 15:06:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
