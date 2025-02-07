/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davioliv <davioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:53:58 by davioliv          #+#    #+#             */
/*   Updated: 2025/02/07 18:09:45 by davioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

void	get_next(t_game *game, int flag, double *next_x, double *next_y);
int		right_utils(t_game *game, int keycode);

int	key_handler(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	if (keycode == ESC)
		exit_project(game, NULL);
	if (keycode == W || keycode == S)
		if (right_utils(game, keycode))
			return (1);
	if (keycode == A || keycode == D)
		if (left_utils(game, keycode))
			return (1);
	if (keycode == LEFT)
	{
		rotate_vector(&game->player->angle, -1);
		perp_vect(&game->player->angle, &game->player->perp);
	}
	if (keycode == RIGHT)
	{
		rotate_vector(&game->player->angle, 1);
		perp_vect(&game->player->angle, &game->player->perp);
	}
	return (1);
}

void	player_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->fmap[++i])
	{
		j = -1;
		while (game->fmap[i][++j])
		{
			if (game->fmap[i][j] == 'P')
			{
				game->player->pos_x = j;
				game->player->pos_y = i;
			}
		}
	}
}

int	check_wall(t_game *game, int flag)
{
	double	next_x;
	double	next_y;

	get_next(game, flag, &next_x, &next_y);
	if (game->fmap[(int)next_y][(int)next_x] == '1' || \
		game->fmap[(int)(next_y + 0.1)][(int)next_x] == '1' || \
		game->fmap[(int)next_y][(int)(next_x + 0.1)] == '1' || \
		game->fmap[(int)(next_y - 0.1)][(int)next_x] == '1' || \
		game->fmap[(int)next_y][(int)(next_x - 0.1)] == '1')
	{
		return (1);
	}
	return (0);
}

void	get_next(t_game *game, int flag, double *next_x, double *next_y)
{
	double	offset;

	offset = 0.3;
	if (flag == 0)
	{
		*next_x = game->player->pos_x + game->player->angle.x * offset;
		*next_y = game->player->pos_y + game->player->angle.y * offset;
	}
	else if (flag == 1)
	{
		*next_x = game->player->pos_x - game->player->angle.x * offset;
		*next_y = game->player->pos_y - game->player->angle.y * offset;
	}
	else if (flag == 2)
	{
		*next_x = game->player->pos_x + game->player->perp.x * offset;
		*next_y = game->player->pos_y + game->player->perp.y * offset;
	}
	else if (flag == 3)
	{
		*next_x = game->player->pos_x - game->player->perp.x * offset;
		*next_y = game->player->pos_y - game->player->perp.y * offset;
	}
}

int	right_utils(t_game *game, int keycode)
{
	if (keycode == W)
	{
		if (check_wall(game, 0))
			return (1);
		game->player->pos_x += game->player->angle.x * 0.1;
		game->player->pos_y += game->player->angle.y * 0.1;
	}
	if (keycode == S)
	{
		if (check_wall(game, 1))
			return (1);
		game->player->pos_x += -game->player->angle.x * 0.1;
		game->player->pos_y += -game->player->angle.y * 0.1;
	}
	return (0);
}
