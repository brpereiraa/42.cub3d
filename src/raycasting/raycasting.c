#include "../includes/cub3d.h"

void	pixel_put(t_data *data, int pixelX, int pixelY);

int ft_raycasting(t_game *game)
{
	//int	hit;
	int	y;
	int	x;
	
	x = (game->player->pos_x * 60);
	y = (game->player->pos_y * 60);
	//hit = 0;
	
	for(int i=0; i<10; i++)
		pixel_put(game->data, x + i, y + i);
	mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0,0);
	return (1);
}


void	pixel_put(t_data *data, int pixelX, int pixelY)
{
	char	*dst;

	int line_length = data->len;
	int bitsppx = data->bits;
	dst = data->addr + (pixelY * line_length + pixelX * (bitsppx / 8));
	*(unsigned int*)dst = GREEN;
}