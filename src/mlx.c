#include "../includes/cub3d.h"

int	ft_mlx_init(t_game *game)
{

	game->data = (t_data *)malloc(sizeof(t_data));
	game->data->mlx = mlx_init();
	game->data->win = mlx_new_window(game->data->mlx, 500, 700, "Cub3D");
	
	minimap_loop(game);
	return (1);
}

void	minimap_loop(t_game *game)
{
	t_data *data;

	data = game->data;
	mlx_hook (data->win, 2, 1L << 0, key_handler, game);
	mlx_loop_hook(data->mlx, ft_render, game);
	mlx_loop (data->mlx);
	return ;
}



void	mlx_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

void destroy_images(t_game *game){
	mlx_destroy_image(game->data->mlx, game->data->img);
}
