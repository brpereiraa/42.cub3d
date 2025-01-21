/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:06:28 by davioliv          #+#    #+#             */
/*   Updated: 2025/01/20 18:34:18 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_cleaner(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL && map[i] != 0)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
//	free(map);
}

static void	clear_mlx(t_game *game)
{
	if (game->data->win)
		mlx_destroy_window(game->data->mlx, game->data->win);
	if (game->data->mlx)
		mlx_destroy_display(game->data->mlx);
	free(game->data);
}

static void	clean_project(t_game *game)
{
	if (game->map)
		free(game->map);
	if (game->player)
		free(game->player);
	if (game->sprites->ceiling)
		free(game->sprites->ceiling);
	if (game->sprites->floor)
		free(game->sprites->floor);
	if (game->sprites)
		free(game->sprites);
	if (game->fv)
		free(game->fv);
	if (game->data)
		clear_mlx(game);
}

void	exit_project(t_game *game, char *msg)
{
	printf("%s\n", msg);
	clean_project(game);
	if (msg)
		exit(1);
	exit(0);
}
