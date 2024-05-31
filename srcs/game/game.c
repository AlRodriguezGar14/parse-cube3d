/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:02:40 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/29 20:11:05 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

double ft_fabs(double x)
{
    if (x < 0)
        return (-x);
    return (x);
}

void ray(t_cube_data *data)
{
    double end_x;
    double end_y;
    double pos_x;
    double pos_y;
    int color;
    t_image_info *img;


    int size = TILE_SIZE;
    int width = size * data->max_x -1;
    int height = size * data->max_y -1;

    pos_x = data->player_position->pos_x / size;
    pos_y = data->player_position->pos_y / size;
    double angle = data->player_position->angle;
    double dir_x = cos(angle); 
    double dir_y = sin(angle); 

    // Shortest distance from the view to hit the wall
    double plane_x = -0.66 * dir_y;
    double plane_y = 0.66 * dir_x;

    img = &data->textures[4];
    color = rgb(255, 0, 255);

    int x = -1;
    int i = 0;
    while (++x < width)
    {
        // ray position
        double camera_x = 2 * x / (double)width - 1;
        //ray direction
        double ray_dir_x = dir_x + plane_x * camera_x;
        double ray_dir_y = dir_y + plane_y * camera_x;

        double delta_dist_x_operation = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
        double delta_dist_y_operation = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));

        // current map position
        int map_x = (int)pos_x;
        int map_y = (int)pos_y;

        // length of the ray from current position to the next x or y side
        double side_dist_x;
        double side_dist_y;

        // length of the ray from one x or y side to the next one
        // 1e30 is an absurd high value to avoid dividing anything by 0
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : delta_dist_x_operation;
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : delta_dist_y_operation;
        double perp_wall_dist;

        // what direction to step (+1 or -1)
        int step_x;
        int step_y;

        bool hit = false;
        int side; // NS or EW

        // Determine step and sidedist
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (pos_x - map_x) * delta_dist_x;
        }
        else 
        {
            step_x = 1;
            side_dist_x = (pos_x + 1 - map_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (pos_y - map_y) * delta_dist_y;
        }
        else 
        {
            step_y = 1;
            side_dist_y = (pos_y + 1 - map_y) * delta_dist_y;
        }

        i = 0;
        while (hit == false)
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
            // printf("player position: y-%d x-%d\n", data->player_position->y, data->player_position->x);
            // printf("Map y[%d]x[%d] = %c\n", map_y, map_x, data->map[map_y][map_x]);
            if (data->map[map_y][map_x] == '1')
                hit = true;
            for (int yy = data->player_position->pos_y; yy != map_y * TILE_SIZE; --yy)
                my_mlx_pixel_put(img, data->player_position->pos_x, yy, color);
            ++i;
        }
        my_mlx_pixel_put(img, x, map_y * TILE_SIZE, color);
    }
    printf("end of loop\n");

}

void init_player(t_cube_data *data)
{
    char c ;
    int p_x;
    int p_y;
    

    c = data->player_position->orientation;

    if(c == 'N')
        data->player_position->angle = 3 * M_PI /  2;
    if(c == 'S')
        data->player_position->angle =  M_PI /  2;
    if(c == 'E')
        data->player_position->angle = 0;
    if(c == 'w')
        data->player_position->angle = M_PI;
    data->player_position->pos_x = (p_x *TILE_SIZE) + TILE_SIZE / 2;
    data->player_position->pos_y = (p_y *TILE_SIZE) + TILE_SIZE / 2;
    data->player_position->fov = (FOV *M_PI/180);
    
    
}
