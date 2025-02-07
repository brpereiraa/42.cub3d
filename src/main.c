/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:10 by bruno             #+#    #+#             */
/*   Updated: 2025/02/07 22:48:11 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (ac != 2)
		return (printf("Invalid number of arguments\n"), 1);
	map_init((&game), av[1]);
	ft_mlx_init(&game);
	exit_project(&game, NULL);
	return (0);
}

void	start_sprites(t_game *game)
{
	ft_memset(game->sprites, 0, sizeof(t_sprites));
	ft_memset(game->data, 0, sizeof(t_data));
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == 32)
		i++;
	return (i);
}
