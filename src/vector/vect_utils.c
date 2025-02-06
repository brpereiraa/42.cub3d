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

void	rotate_vector(t_vect *vector, int degree)
{
	double	angle;
	double	tx;
	double	ty;

	angle = degree * ((double)PI / 180);
	tx = vector->x;
	ty = vector->y;
	vector->x = tx * cos(angle) - ty * sin(angle);
	vector->y = tx * sin(angle) + ty * cos(angle);
}

t_vect	*new_vect(double x, double y)
{
	t_vect	*vector;

	vector = malloc(sizeof(t_vect));
	vector->x = x;
	vector->y = y;
	return (vector);
}

void	perp_vect(t_vect *v1, t_vect *v2)
{
	v2->x = v1->y;
	v2->y = -v1->x;
}
