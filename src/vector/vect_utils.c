/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:03:27 by brpereir          #+#    #+#             */
/*   Updated: 2024/11/22 18:09:38 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate(t_game *game, int degree)
{
	double angle;
	double vx;
	double vy;

	vx = game->fv->x;
	vy = game->fv->y;
	angle = degree * ((double)3.1415 / 180);
	game->fv->x = vx * cos(angle) - vy * sin(angle);
	game->fv->y = vx * sin(angle) + vy * cos(angle);
	
}