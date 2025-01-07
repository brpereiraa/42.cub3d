/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:10 by bruno             #+#    #+#             */
/*   Updated: 2024/11/08 18:20:58 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Invalid number of arguments\n"), 1);
	if (!map_init((&game), av[1]))
		return (printf("Invalid map\n"), 1);
	ft_mlx_init(&game);
	return (0);
}
