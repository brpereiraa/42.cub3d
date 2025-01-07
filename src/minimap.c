#include "../includes/cub3d.h"

void draw_wall(t_game *game, int i, int j);

int mmap_init(t_game *game)
{
	render_images(game);	
	return (1);
}

void	put_image_to_window(t_game *game, int i, int j)
{
	t_data	*data;

	int size = 50;
	data = game->data;

	if (game->fmap[i][j] == '1')
		draw_wall(game, j*10, i*10);
	mlx_put_image_to_window(data->mlx, data->win, game->data->img, 0, 0);
	return ;
}

void	render_images(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while(game->fmap[++i])
	{
		j = -1;
		while(game->fmap[i][++j])
			put_image_to_window(game, i, j);
	}

	return ;
}

void draw_wall(t_game *game, int i, int j)
{
	int size = 10;
	int k = -1;
	int l = -1;

	while(++k < size){
		l = -1;
		while(++l < size)
			pixel_put(game->data, i + l, j + k, GREEN);
	}
}