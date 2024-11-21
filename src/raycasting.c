#include "../includes/cub3d.h"

int ft_raycasting(t_game *game)
{
	//int	hit;

	game->vector = (t_vect *)malloc(sizeof(t_vect));
	game->vector->y = 0;
	game->vector->x = 1;
	//hit = 0;
	
	for(int i=0; i<100; i++)
		mlx_pixel(game->data, game->player->pos_x + i, game->player->pos_y + i, 0x00FF0000);
	mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0,0);
	return (1);
}
