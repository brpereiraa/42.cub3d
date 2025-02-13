/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:10 by bruno             #+#    #+#             */
/*   Updated: 2025/02/12 23:57:59 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	ft_bzero(&game, sizeof(t_game));
	start_sprites(&game);
	map_init((&game), av[1]);
	ft_mlx_init(&game);
	exit_project(&game, NULL);
	return (0);
}

void	start_sprites(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	game->sprites = malloc(sizeof(t_sprites));
	game->data = malloc(sizeof(t_data));
	ft_memset(game->player, 0, sizeof(t_player));
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
