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
    double p_x;
    double p_y;
    int color;
    t_image_info *img;

    p_x = data->player_position->pos_x;
    p_y = data->player_position->pos_y;

    double base_x = p_x;
    double base_y = p_y;
    img = &data->textures[4];
    color = rgb(255, 0, 0);
    double step = 1.0;

    double min_angle = data->player_position->angle - FOV * M_PI / 180;
    double max_angle = data->player_position->angle + FOV * M_PI / 180;

    double increment = 1 * M_PI / 180;
    double i = min_angle;
    while (i < max_angle)
    {
        double ray_dir_x = cos(i);
        double ray_dir_y = sin(i);

        end_x = p_x + ray_dir_x * 350;
        end_y = p_y + ray_dir_y * 350;
        if (end_x < 0) end_x = 0;
        if (end_y < 0) end_y = 0;
        if (end_x >= TILE_SIZE * data->max_x) end_x = TILE_SIZE * data->max_x -1;
        if (end_y >= TILE_SIZE * data->max_y) end_y = TILE_SIZE * data->max_y -1;


        double dx = end_x - p_x;
        double dy = end_y - p_y;
        double d = sqrt(dx * dx + dy * dy);
        double step_x = step * (dx / d);
        double step_y = step * (dy / d);

        while (fabs(end_x - p_x) > 0.1 || fabs(end_y - p_y) > 0.1)
        {
            my_mlx_pixel_put(img, p_x, p_y, color);
            p_x += step_x;
            p_y += step_y;
        }
        p_x = base_x;
        p_y = base_y;
        i += increment;
    }
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
