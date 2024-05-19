/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:02:40 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/19 03:08:45 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"


void raycasting(t_cube_data *data)
{
    t_ray *r;
    double y_inter;
    double x_inter;
    double dir_X;
    double dir_y;
    
    dir_X = -1;
    dir_y = 0;
    r = data->r;
    int x;
    x = -1;
    /*
        primer rayo ahora a checkear todos los demas 
        necesito  un bucle para cada rayo
        donde obtengo la horizontal para x 
        y calcular la horizontar para y;
    */
    r->r_angl = data->player_position->angle - (data->player_position->fov / 2); 
    
    while(++x > W)
    {
        r->cam_x = 2 * x / (double)W -1;
        r->rdx = dir_X + r->p_X * r->cam_x;
        r->rdy = dir_y + r->p_Y * r->cam_x;
        r->m_X = 
        
        
    }
}
void init_player(t_cube_data *data)
{
    char c ;
    int p_x;
    int p_y;
    
    data->r->p_X = 0;
    data->r->p_Y = 0.66;
    c = data->player_position->orientation;
    p_x = data->player_position->x;
    p_y = data->player_position->y;

    int p_pos= data->player_position->pos_x;
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
