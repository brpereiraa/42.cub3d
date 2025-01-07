#include "../includes/cub3d.h"

unsigned int get_pixel_color(void *texture, int tex_x, int tex_y, int texture_width)
{
    char *data;
    int bpp, size_line, endian;

    data = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
    int offset = (tex_y * size_line) + (tex_x * (bpp / 8));
    return *(unsigned int *)(data + offset);
}

void pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) // Replace WIDTH/HEIGHT with SCREEN_WIDTH/SCREEN_HEIGHT macros if defined
        return;

    dst = data->addr + (y * data->len + x * (data->bits / 8));
    *(unsigned int *)dst = color;
}

void draw_vertical_line(t_game *game, int screen_x, int wall_height, double wall_x, int side, double ray_dir_x, double ray_dir_y)
{
    int start = -wall_height / 2 + 300; // Center of screen
    int end = wall_height / 2 + 300;

    if (start < 0)
        start = 0;
    if (end >= HEIGHT) // SCREEN_HEIGHT
        end = HEIGHT - 1;

    int texture_width = 64;
    int texture_height = 64;

    // Select texture based on wall side
    void *texture;
    if (side == 0)
        texture = (ray_dir_x < 0) ? game->sprites->west : game->sprites->east;
    else
        texture = (ray_dir_y > 0) ? game->sprites->north : game->sprites->south;

    int tex_x = (int)(wall_x * (double)texture_width);
    if (side == 0 && ray_dir_x < 0) // West wall
        tex_x = texture_width - tex_x - 1;
    else if (side == 1 && ray_dir_y > 0) // North wall
        tex_x = texture_width - tex_x - 1;

    double step = 1.0 * texture_height / wall_height;
    double tex_pos = (start - 300 + wall_height / 2) * step;

    for (int y = start; y < end; y++)
    {
        int tex_y = (int)tex_pos & (texture_height - 1);
        tex_pos += step;

        unsigned int color = get_pixel_color(texture, tex_x, tex_y, texture_width);
        pixel_put(game->data, screen_x, y, color);
    }
}

void cast_single_ray(t_game *game, double ray_dir_x, double ray_dir_y, int screen_x)
{
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
    double side_dist_x, side_dist_y;
    int step_x, step_y;

    int map_x = (int)game->player->pos_x;
    int map_y = (int)game->player->pos_y;

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (game->player->pos_x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - game->player->pos_x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (game->player->pos_y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - game->player->pos_y) * delta_dist_y;
    }

    int hit = 0;
    int side;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }

        if (game->fmap[map_y][map_x] == '1')
            hit = 1;
    }

    double wall_dist = (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);
    int wall_height = (int)(HEIGHT / wall_dist); // SCREEN_HEIGHT

    double wall_x;
    if (side == 0)
        wall_x = game->player->pos_y + wall_dist * ray_dir_y;
    else
        wall_x = game->player->pos_x + wall_dist * ray_dir_x;
    wall_x -= floor(wall_x);

    draw_vertical_line(game, screen_x, wall_height, wall_x, side, ray_dir_x, ray_dir_y);
}

int ft_raycasting(t_game *game)
{
    double plane_x = game->player->perp.x;
    double plane_y = game->player->perp.y;
    double dir_x = game->player->angle.x;
    double dir_y = game->player->angle.y;

    for (int x = 0; x < WIDTH; x++) // SCREEN_WIDTH = WIDTH
    {
        double camera_x = 1 - 2 * x / (double)WIDTH;
        double ray_dir_x = dir_x + plane_x * camera_x;
        double ray_dir_y = dir_y + plane_y * camera_x;

        cast_single_ray(game, ray_dir_x, ray_dir_y, x);
    }

    mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0, 0);
    return (1);
}
