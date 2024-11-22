#include "../includes/cub3d.h"

int ft_raycasting(t_game *game)
{
	//int	hit;
	int	y;
	int	x;
	
	x = (game->player->pos_x * 60);
	y = (game->player->pos_y * 60);
	//hit = 0;
	
	for(int i=0; i<10; i++)
		mlx_pixel(game->data, x + i, y + i, 0x00FF0000);
	mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0,0);
	return (1);
}
