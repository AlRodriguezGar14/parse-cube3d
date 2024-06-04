/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:02:40 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/31 20:14:32alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int ray(void *arg)
{
    
    t_cube_data *data;
    data = (t_cube_data *)arg;
    moves(data);
    int size = TILE_SIZE;
    int width = size * data->max_x -1;
    int height = size * data->max_y -1;
    t_image_info *img;

    img = renew_image(data);
    // Variables for the end and start position of the ray, the color of the ray and the image where the ray is drawn.
    double end_x;
    double end_y;
    //double pos_x;
    //double pos_y;
    int color;

    // The size of a tile in the game, the width and height of the game screen.

    // The position of the player and the direction of the player.
    data->r.pos_x = data->player_position->pos_x / size;
    data->r.pos_y = data->player_position->pos_y / size;

    double angle = data->player_position->angle;
    double dir_x = cos(angle); 
    double dir_y = sin(angle); 

    // The plane the player is looking at (perpendicular to the player's direction).
    double plane_x = -0.66 * dir_y;
    double plane_y = 0.66 * dir_x;

    // The image where the ray is drawn and the color of the ray.
    color = rgb(255, 0, 255);

    // The main loop where the raycasting happens.
    int x = -1;
    int i = 0;
    while (++x < width)
    {
        // Calculate the ray position and direction from the camera plane.
        double camera_x = 2 * x / (double)width - 1;
        double ray_dir_x = dir_x + plane_x * camera_x;
        double ray_dir_y = dir_y + plane_y * camera_x;

        // The map square the ray is in.
        int map_x = (int)data->r.pos_x;
        int map_y = (int)data->r.pos_y;

        // The length of the ray from one x or y-side to the next x or y-side.
        double side_dist_x;
        double side_dist_y;

        // The length of the ray from the current position to the next x or y-side.
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        // The perpendicular distance to the wall (this is what will be used to compute the height of the wall slice).
        double perp_wall_dist;

        // The direction to step in (+1 or -1).
        int step_x;
        int step_y;

        // Whether or not a wall was hit.
        bool hit = false;

        // Whether the wall hit was a x-side or a y-side of a square.
        int side;

        // Calculate step direction and initial side_dist.
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->r.pos_x - map_x) * delta_dist_x;
        }
        else 
        {
            step_x = 1;
            side_dist_x = (data->r.pos_x + 1 - map_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->r.pos_y - map_y) * delta_dist_y;
        }
        else 
        {
            step_y = 1;
            side_dist_y = (data->r.pos_y + 1 - map_y) * delta_dist_y;
        }

        // Perform DDA (Digital Differential Analysis) to find where the ray hits a wall.
        while (hit == false)
        {
            // If the horizontal distance to the next grid line is smaller, move in the x-direction
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x; // Increase the horizontal distance counter
                map_x += step_x; // Move to the next grid square in the x-direction
                side = 0; // Indicate that we moved in the x-direction
            }
            // Otherwise, the vertical distance is smaller, so move in the y-direction
            else
            {
                side_dist_y += delta_dist_y; // Increase the vertical distance counter
                map_y += step_y; // Move to the next grid square in the y-direction
                side = 1; // Indicate that we moved in the y-direction
            }
            // If we've hit a wall (indicated by '1' in the map), stop moving
            if (data->map[map_y][map_x] == '1')
                hit = true;
        }

        // Calculate the distance to the wall.
        // If we moved in the x-direction, calculate using x-coordinates
        if (side == 0)
            // The distance is calculated as follows:
            // - Start with the x-coordinate of the wall (map_x)
            // - Subtract the x-coordinate of the player's position (pos_x)
            // - Add half of the step size in the x-direction ((1 - step_x) / 2)
            //   This is to adjust for the fact that the ray may have hit the wall anywhere between the start and end of the wall square, not just at the exact center.
            // - Divide by the x-component of the ray direction (ray_dir_x) to convert the distance from map units to world units.
            perp_wall_dist = (map_x - data->r.pos_x + (1 - step_x) / 2) / ray_dir_x;
        // Otherwise, we moved in the y-direction, so calculate using y-coordinates
        else
            perp_wall_dist = (map_y - data->r.pos_y + (1 - step_y) / 2) / ray_dir_y;

        // Calculate the height of the wall slice.
        // This is inversely proportional to the distance to the wall, to create the perspective effect
        int line_height = (int)(height / perp_wall_dist);

        // Calculate the start position of the wall slice for this ray.
        // The wall slice is vertically centered in the screen, so we start at half the screen height (height / 2)
        // Then we subtract half the height of the wall slice (-line_height / 2) to move up to the start of the wall slice
        // If the result is negative (i.e., off the top of the screen), we clamp it to 0
        int draw_start = -line_height / 2 + height / 2;
        if (draw_start < 0)
            draw_start = 0;

        // Calculate the end position of the wall slice for this ray.
        // Similar to the start position, we start at half the screen height (height / 2)
        // But this time we add half the height of the wall slice (line_height / 2) to move down to the end of the wall slice
        // If the result is greater than the screen height (i.e., off the bottom of the screen), we clamp it to the screen height minus 1
        int draw_end = line_height / 2 + height / 2;
        if (draw_end >= height)
            draw_end = height - 1;
        // Choose wall color based on the side that was hit.
        // If we hit a wall in the y-direction, color it green, otherwise color it blue
        // The color intensity is inversely proportional to the distance to the wall
        if (side == 1)
            color = rgb(0, 255 * (1.0 / perp_wall_dist), 0);
        else
            color = rgb(0, 0, 255 * (1.0 / perp_wall_dist));

        // Draw the wall slice.
        // For each pixel in the vertical line, put the chosen color
        int base = draw_start;
        while (++base != draw_end)
            my_mlx_pixel_put(img, x, base, color);
        // Draw the ceiling and floor.
        int top = draw_end - 1;
        while (++top != height)
            my_mlx_pixel_put(img, x, top, rgb(255, 255, 0));
        int bottom = draw_start + 1;
        while (--bottom != -1)
            my_mlx_pixel_put(img, x, bottom, rgb(255, 0, 255));
    }
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, img->image_charge, 0, 0);
   mlx_destroy_image(data->mlx->mlx, img->image_charge);

    // Print a message to the console to indicate that the image has been rendered.
   // printf("image rendered\n");
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