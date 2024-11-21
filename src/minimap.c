#include "../includes/cub3d.h"

int mmap_init(t_game *game)
{
	destroy_images(game);
	put_image(game);	

	return (1);
}

void	put_image_to_window(t_game *game, int i, int j)
{
	t_data	*data;
	void	*wall;

	int size = 50;
	data = game->data;

	wall = mlx_xpm_file_to_image(data->mlx, "./sprites/parede.xpm", &size, &size);

	if (game->fmap[i][j] == '1')
		mlx_put_image_to_window(data->mlx, data->win, wall, j * 50, i * 50);

	ft_raycasting(game);
	return ;
}

void	put_image(t_game *game)
{
	int	i;
	int	j;
	t_data	*data;

	i = -1;
	data = game->data;
	while(game->fmap[++i])
	{
		j = -1;
		while(game->fmap[i][++j])
			put_image_to_window(game, i, j);
	}

	void	*player;
	int size = 50;
//	player = mlx_xpm_file_to_image(data->mlx, "./sprites/player.xpm", &size, &size);
//	mlx_put_image_to_window(data->mlx, data->win, player, game->player->pos_x * 50, game->player->pos_y * 50);
	return ;
}
