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
    img = &data->textures[4];
    //color en rojo 
    color = rgb(255, 0, 0);
    double step = 1.0;

    end_x= p_x +cos(data->player_position->fov) * 100;
    end_y=p_y +sin(data->player_position->fov) * 100;
    
    printf("angle%f\n",data->player_position->angle);
    printf("end_x %f end_y %f\n",end_x,end_y);
    printf("p_x %f p_y %f\n",p_x,p_y);
    
    while (end_x != p_x || end_y != p_y)
    {
        //printf("p_x%fp_y%f\n",p_x,p_y);
        
         my_mlx_pixel_put(img, p_x, p_y, color);
        double dx = end_x - p_x;
        double dy = end_y - p_y;
        double d = sqrt(dx * dx + dy * dy);
        double step_x = step * (dx / d);
        double step_y = step * (dy / d);
        
        p_x+=step_x;
        p_y+=step_y;
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
    data->player_position->fov = (-30 *M_PI/180);
    
    
}
