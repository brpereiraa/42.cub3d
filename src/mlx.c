#include "../includes/cub3d.h"

void	minimap_loop(t_game *game)
{
	mlx_hook (game->win, 17, 1L << 2, close_window, game);
	mlx_hook (game->mlx);
}
