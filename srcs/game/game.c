/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:12:58 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/09 00:01:14 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/parsecube.h"

int ray(void *arg)
{
    t_cube_data *data;
    data = (t_cube_data *)arg;
    moves(data);

    int size = TILE_SIZE;
    int width = WIDTH;
    int height = HEIGHT;
    t_image_info *img;

    img = renew_image(data);

    double end_x;
    double end_y;
    int color;
    
    if(!data->r.pos_x && !data->r.pos_y)
    {
        data->r.pos_x = data->player_position->pos_x / size;
        data->r.pos_y = data->player_position->pos_y / size;
    }

    double angle = data->player_position->angle;
    double dir_x = cos(angle); 
    double dir_y = sin(angle); 

    double plane_x = 0.66 * dir_y;
    double plane_y = -0.66 * dir_x;

    color = rgb(255, 0, 255);

    int x = -1;
    while (++x < WIDTH)
    {
        double camera_x = 2 * x / (double)width - 1;
        double ray_dir_x = dir_x + plane_x * camera_x;
        double ray_dir_y = dir_y + plane_y * camera_x;

        if (ray_dir_y == 0.0 || ray_dir_x == 0.0)
            return 1;

        int map_x = (int)data->r.pos_x;
        int map_y = (int)data->r.pos_y;

        double side_dist_x;
        double side_dist_y;

        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
         
        double perp_wall_dist;

        int step_x;
        int step_y;

        bool hit = false;
        int side;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->r.pos_x - map_x) * delta_dist_x;
        }
        else 
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->r.pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->r.pos_y - map_y) * delta_dist_y;
        }
        else 
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->r.pos_y) * delta_dist_y;
        }

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
            if (data->map[map_y][map_x] == '1')
                hit = true;
        }

        if (side == 0)
            perp_wall_dist = (map_x - data->r.pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - data->r.pos_y + (1 - step_y) / 2) / ray_dir_y;

        if (perp_wall_dist == 0.0)
            perp_wall_dist = 0.1;

        int line_height = (int)(HEIGHT / perp_wall_dist);

        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;

        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        t_image_info *texture;
        
        texture = get_texture(data, side);


        int base = draw_start;
        
        
        while (++base != draw_end)
        {
            if (x < width && base < height && base > 0 && x > 0)
            {
                funcion_que_sirve_para_saber_que_pixel_coger();
                color = get_texture_color(texture, data->wall.tex_x, data->wall.tex_num);
                my_mlx_pixel_put(img, x, base, color, width, height);
            }
        }

        int top = draw_end - 1;
        while (++top != HEIGHT)
            my_mlx_pixel_put(img, x, top, rgb(255, 255, 0), width, height);
        int bottom = draw_start + 1;
        while (--bottom != -1)
            my_mlx_pixel_put(img, x, bottom, rgb(255, 0, 255), width, height);
    }

    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, img->image_charge, 0, 0);
    mlx_destroy_image(data->mlx->mlx, img->image_charge);
}


void init_player(t_cube_data *data)
{
    char c ;
    int p_x;
    int p_y;
    
    p_y = data->player_position->pos_y / TILE_SIZE;
    p_x = data->player_position->pos_x / TILE_SIZE;

    c = data->player_position->orientation;

    if(c == 'N')
        data->player_position->angle = 3 * M_PI /  2;
    if(c == 'S')
        data->player_position->angle =  M_PI /  2;
    if(c == 'E')
        data->player_position->angle = 0;
    if(c == 'W')
        data->player_position->angle = M_PI;
    data->player_position->pos_x = (p_x *TILE_SIZE) + TILE_SIZE / 2;
    data->player_position->pos_y = (p_y *TILE_SIZE) + TILE_SIZE / 2;
    data->player_position->fov = (FOV *M_PI/180);
    
}
