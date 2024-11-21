#include "../includes/cub3d.h"

int	key_handler(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	if (keycode == ESC)
		exit(1);
	if (keycode == W)
		game->player->pos_y -= 0.1;
	if (keycode == S)
		game->player->pos_y += 0.1;
	if (keycode == A)
		game->player->pos_x -= 0.1;
	if (keycode == D)
		game->player->pos_x += 0.1;
	if (keycode == LEFT)
		game->vector->x += 0.2;
	if (keycode == RIGHT)
		game->vector->x -= 0.2;
	mmap_init(game);
	return (1);
}

void	player_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while(game->fmap[++i])
	{
		j = -1;
		while(game->fmap[i][++j])
			if (game->fmap[i][j] == 'P')
			{
				game->player->pos_x = j;
				game->player->pos_y = i;
			}
	}
}
