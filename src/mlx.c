#include "../includes/cub3d.h"

int	ft_mlx_init(t_game *game)
{
	game->data = (t_data *)malloc(sizeof(t_data));
	
	start_window(game);
	minimap_loop(game);
	destroy_images(game);
	return (1);
}

void	minimap_loop(t_game *game)
{
	t_data *data;

	data = game->data;

	//mlx_hook (game->win, 17, 1L << 2, close_window, game);
	mlx_hook (data->win, 2, 1L << 0, key_handler, game);
	mlx_loop (data->mlx);
	return ;
}

int	start_window(t_game *game)
{
	t_data	*data;
	
	data = game->data;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (printf("Error starting mlx.\n"), 0);
	data->win = mlx_new_window(data->mlx, 20 * 20, 20 * 20, "Juan");
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits, &data->len, &data->endian);
	if (!data->win)
		return (printf("Error starting win.\n"), 0);
	if (!data->win)
		return (printf("Error starting img.\n"), 0);
	mmap_init(game);
	return (1);
}

void	mlx_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

void destroy_images(t_game *game){
	mlx_clear_window(game->data->mlx, game->data->win);
}
