#include "../includes/cub3d.h"

void	minimap_loop(t_game *game)
{
	mlx_hook (game->win, 17, 1L << 2, close_window, game);
	mlx_hook (game->mlx);
}

int	ft_mlx_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error starting mlx.\n"), 1);
	game->win = mlx_new_window(game->mlx, 20 * 20, 20 * 20);
}
