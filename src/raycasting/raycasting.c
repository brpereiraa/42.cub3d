#include "../includes/cub3d.h"
#include <math.h>

// Function prototypes
void cast_single_ray(t_game *game, double ray_dir_x, double ray_dir_y, int screen_x);
void draw_vertical_line(t_data *data, int x, int wall_height);

// Main raycasting function
int ft_raycasting(t_game *game)
{
    double ray_dir_x, ray_dir_y;

    // Cast rays for each column of the screen
    for (int x = 0; x < WIDTH; x++)
    {
        // Calculate ray direction using the forward vector (angle) and perpendicular vector
        ray_dir_x = game->player->angle.x + (2 * (x / (double)WIDTH) - 1) * game->player->perp.x;
        ray_dir_y = game->player->angle.y + (2 * (x / (double)WIDTH) - 1) * game->player->perp.y;

        // Cast a single ray with the computed direction
        cast_single_ray(game, ray_dir_x, ray_dir_y, x);
    }

    // Display the rendered image
    mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0, 0);
    return (1);
}

// Function to cast a single ray
void cast_single_ray(t_game *game, double ray_dir_x, double ray_dir_y, int screen_x)
{
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
    double side_dist_x, side_dist_y;
    int step_x, step_y;

    int map_x = (int)game->player->pos_x;
    int map_y = (int)game->player->pos_y;

    // Determine step and initial side distances
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

    // Perform DDA (Digital Differential Analysis)
    int hit = 0;
    int side;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0; // Vertical wall hit
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1; // Horizontal wall hit
        }

        // Check if ray has hit a wall
        if (game->fmap[map_y][map_x] == '1')
            hit = 1;
    }

    // Calculate distance to wall
    double wall_dist = (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);

    // Project wall height to screen
    int wall_height = (int)(HEIGHT / wall_dist);

    // Draw the vertical line for this ray
    draw_vertical_line(game->data, screen_x, wall_height);
}

// Function to draw a vertical line (wall slice) for a ray
void draw_vertical_line(t_data *data, int x, int wall_height)
{
    int start = -wall_height / 2 + HEIGHT / 2;
    int end = wall_height / 2 + HEIGHT / 2;

    if (start < 0) start = 0;
    if (end >= HEIGHT) end = HEIGHT - 1;

    for (int y = start; y <= end; y++)
    {
        pixel_put(data, x, y); // Draw a pixel at (x, y)
    }
}

void pixel_put(t_data *data, int x, int y)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return; // Prevent out-of-bounds errors

    int line_length = data->len;
    int bitsppx = data->bits;
    dst = data->addr + (y * line_length + x * (bitsppx / 8));
    *(unsigned int *)dst = 0x00FF00; // Color (Green)
}
