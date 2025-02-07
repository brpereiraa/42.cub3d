/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:49:37 by davioliv          #+#    #+#             */
/*   Updated: 2025/02/07 22:46:08 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	left_utils(t_game *game, int keycode)
{
	if (keycode == A)
	{
		if (check_wall(game, 2))
			return (1);
		game->player->pos_x += game->player->perp->x * 0.1;
		game->player->pos_y += game->player->perp->y * 0.1;
	}
	if (keycode == D)
	{
		if (check_wall(game, 3))
			return (1);
		game->player->pos_x += -game->player->perp->x * 0.1;
		game->player->pos_y += -game->player->perp->y * 0.1;
	}
	return (0);
}
