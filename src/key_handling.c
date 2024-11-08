#include "../includes/cub3d.h"

int	key_handler(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	if (keycode == ESC)
			exit(1);
	return (1);
}
