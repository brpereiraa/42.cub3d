#include "../includes/cub3d.h"

int	ft_mlx_init(t_game *game)
{
	start_window(game);
	minimap_loop(game);
	return (1);
}

void	minimap_loop(t_game *game)
{
	//mlx_hook (game->win, 17, 1L << 2, close_window, game);
	mlx_hook (game->win, 2, 1L << 0, key_handler, game);
	mlx_loop (game->mlx);
	return ;
}

int	start_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error starting mlx.\n"), 0);
	game->win = mlx_new_window(game->mlx, 20 * 20, 20 * 20, "Juan");
	game->img = mlx_new_image(game->mlx, 1920, 1080);
	if (!game->win)
		return (printf("Error starting win.\n"), 0);
	if (!game->win)
		return (printf("Error starting img.\n"), 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

int	key_handler(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	if (keycode == ESC)
			exit(1);
	return (1);
}
