#include "../includes/cub3d.h"
#include <math.h>

int	check_wall(t_game *game, int flag);

int	key_handler(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	if (keycode == ESC)
		exit(1);
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
	if (keycode == A)
	{
		if (check_wall(game, 2))
			return (1);
		game->player->pos_x += game->player->perp.x * 0.1;
		game->player->pos_y += game->player->perp.y * 0.1;
	}
	if (keycode == D)
	{
		if (check_wall(game, 3))
			return (1);
		game->player->pos_x += -game->player->perp.x * 0.1;
		game->player->pos_y += -game->player->perp.y * 0.1;
	}
	if (keycode == LEFT)
		rotate_vector(&game->player->angle, -1), perp_vect(&game->player->angle, &game->player->perp);
	if (keycode == RIGHT)
		rotate_vector(&game->player->angle, 1), perp_vect(&game->player->angle, &game->player->perp);
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
	if (flag == 0)
	{
		if (game->fmap[(int)(game->player->pos_y + game->player->angle.y * 0.1)][(int)(game->player->pos_x + game->player->angle.x * 0.1)] == '1')
			return (1);
	}
	if (flag == 1)
	{
		if (game->fmap[(int)(game->player->pos_y - game->player->angle.y * 0.1)][(int)(game->player->pos_x - game->player->angle.x * 0.1)] == '1')
			return (1);
	}
	if (flag == 2)
	{
		if (game->fmap[(int)(game->player->pos_y + game->player->perp.y * 0.1)][(int)(game->player->pos_x + game->player->perp.x * 0.1)] == '1')
			return (1);
	}
	if (flag == 3)
	{
		if (game->fmap[(int)(game->player->pos_y - game->player->perp.y * 0.1)][(int)(game->player->pos_x - game->player->perp.x * 0.1)] == '1')
			return (1);
	}
	return (0);
}
