#include "../includes/cub3d.h"

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

	// if (game->fmap[i][j] == '1')
	// 	mlx_put_image_to_window(data->mlx, data->win, game->sprites->wall, j * 50, i * 50);
	// mlx_put_image_to_window(data->mlx, data->win, game->sprites->player, game->player->pos_x * 50, game->player->pos_y * 50);
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
