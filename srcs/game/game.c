/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:12:58 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/10 12:47:04 by dgomez-m         ###   ########.fr       */
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
            data->r.perpwalldist = (map_x - data->r.pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            data->r.perpwalldist = (map_y - data->r.pos_y + (1 - step_y) / 2) / ray_dir_y;

        if (data->r.perpwalldist == 0.0)
            data->r.perpwalldist = 0.1;

         data->wall.line_h = (int)(HEIGHT / data->r.perpwalldist);

         data->wall.draw_start = -data->wall.line_h / 2 + HEIGHT / 2;
        if (data->wall.draw_start < 0) data->wall.draw_start = 0;

        data->wall.draw_end = data->wall.line_h / 2 + HEIGHT / 2;
        if (data->wall.draw_end >= HEIGHT) data->wall.draw_end = HEIGHT - 1;

        t_image_info *texture = get_texture(data, side);

        double wall_x;
        if (side == 0)
            wall_x = data->r.pos_y + data->r.perpwalldist * ray_dir_y;
        else
            wall_x = data->r.pos_x + data->r.perpwalldist * ray_dir_x;
        wall_x -= floor(wall_x);

        int tex_x = (int)(wall_x * (double)(300));
        if (side == 0 && ray_dir_x > 0) tex_x = 300 - tex_x - 1;
        if (side == 1 && ray_dir_y < 0) tex_x = 300 - tex_x - 1;
        int y = data->wall.draw_start - 1;
        while (++y < data->wall.draw_end)
        {
            // Calculo de la posición en la textura
            int d = y * 256 - HEIGHT * 128 + data->wall.line_h * 128;
            int tex_y = ((d * 300) / data->wall.line_h) / 256;

            // Asegurarnos de que tex_y esté dentro de los límites de la textura
            if (tex_y < 0) tex_y = 0;
            if (tex_y >= 300) tex_y = 299;

            // Obtener el color de la textura
            color = get_texture_color(texture, tex_x, tex_y);

            // Dibujar el pixel en la imagen
            my_mlx_pixel_put(img, x, y, color, width, height);

           
        }
        int top = data->wall.draw_end - 1;
        while (++top != HEIGHT)
            my_mlx_pixel_put(img, x, top, rgb(255, 255, 0), width, height);
        int bottom = data->wall.draw_start + 1;
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
