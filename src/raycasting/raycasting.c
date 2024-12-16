#include "../includes/cub3d.h"

void cast_rays(t_game *game, t_vect *perp);

int ft_raycasting(t_game *game)
{
    int x, y;
    double t;
    t_vect ray_dir;

    x = (game->player->pos_x * 60);
    y = (game->player->pos_y * 60);

    t = 0;
    while (t <= 1)
    {
        ray_dir.x = t * game->player->perp.x;
        ray_dir.y = t * game->player->perp.y;
        cast_rays(game, &ray_dir);
        ray_dir.x = t * -game->player->perp.x;
        ray_dir.y = t * -game->player->perp.y;
        cast_rays(game, &ray_dir);
        t += 0.001;
    }

    mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0, 0);
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

void cast_rays(t_game *game, t_vect *perp)
{
	t_vect vect;

	double i = 0;
	vect = *new_vect(game->player->pos_x, game->player->pos_y);
	while(game->fmap[(int)vect.y][(int)vect.x] != '1')
	{
		vect.x += game->player->angle.x * i + perp->x * i;
		vect.y += game->player->angle.y * i + perp->y * i;
		pixel_put(game->data, vect.x * 50, vect.y * 50);
		i += 0.001;
	}
}