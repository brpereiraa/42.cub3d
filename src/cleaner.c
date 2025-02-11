/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:06:28 by davioliv          #+#    #+#             */
/*   Updated: 2025/02/10 23:13:21 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dp_cleaner(char **var)
{
	int	i;

	i = 0;
	if (!var)
		return ;
	while (var[i] != NULL)
	{
		if (var[i])
			free(var[i]);
		i++;
	}
	free(var);
}

static void	clear_mlx(t_game *game)
{
	if (game->data->win)
		mlx_destroy_window(game->data->mlx, game->data->win);
	if (game->data->mlx)
	{
		mlx_destroy_display(game->data->mlx);
		free(game->data->mlx);
	}
	free(game->data);
}

static void	clear_sprites(t_game *game)
{
	if (game->sprites->csouth)
		free(game->sprites->csouth);
	if (game->sprites->ceast)
		free(game->sprites->ceast);
	if (game->sprites->cnorth)
		free(game->sprites->cnorth);
	if (game->sprites->cwest)
		free(game->sprites->cwest);
	if (game->sprites->east)
		mlx_destroy_image(game->data->mlx, game->sprites->east);
	if (game->sprites->north)
		mlx_destroy_image(game->data->mlx, game->sprites->north);
	if (game->sprites->south)
		mlx_destroy_image(game->data->mlx, game->sprites->south);
	if (game->sprites->west)
		mlx_destroy_image(game->data->mlx, game->sprites->west);
	free(game->sprites);
}

static void	clean_project(t_game *game)
{
	if (game->map)
		dp_cleaner(game->map);
	if (game->player->angle)
		free(game->player->angle);
	if (game->player->perp)
		free(game->player->perp);
	if (game->player)
		free(game->player);
	if (game->sprites)
		clear_sprites(game);
	if (game->fv)
		free(game->fv);
	if (game->data)
		clear_mlx(game);
}

void	exit_project(t_game *game, char *msg)
{
	clean_project(game);
	if (msg)
	{
		printf("Error\n%s", msg);
		exit(1);
	}
	exit(0);
}
