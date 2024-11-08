#include "../includes/cub3d.h"

int mmap_init(t_game *game)
{
	put_image(game);	

	return (1);
}

void	put_image_to_window(t_game *game, int i, int j)
{
	t_data	*data;
	void	*wall;
	void	*player;

	int size = 50;
	data = game->data;

	wall = mlx_xpm_file_to_image(data->mlx, "./sprites/parede.xpm", &size, &size);
	player = mlx_xpm_file_to_image(data->mlx, "./sprites/player.xpm", &size, &size);

	if (game->fmap[i][j] == '1')
		mlx_put_image_to_window(data->mlx, data->win, wall, j * 50, i * 50);
	if (game->fmap[i][j] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, player, j * 50, i * 50);

	return ;
}

void	put_image(t_game *game)
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
