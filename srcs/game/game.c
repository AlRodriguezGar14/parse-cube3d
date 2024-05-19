/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:02:40 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/19 06:05:37 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

void calculat_step(t_ray *r)
{
    if (r->rdx < 0)
	{
        r->step_x = -1;
        r->side_x = (r->p_X - r->m_X) * r->h_x;
    }
    else
    {
        r->step_x = 1;
        r->side_x = (r->m_X + 1.0 - r->p_X) * r->h_x;
    }
    if (r->rdy < 0)
    {
        r->step_y = -1;
        r->side_y = (r->p_Y - r->m_Y) * r->h_y;
    }
    else
    {
        r->step_y = 1;
        r->side_y = (r->m_Y + 1.0 - r->p_Y) * r->h_y;
    }
}
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
    r->r_angl = data->player_position->angle - (data->player_position->fov / 2); 
    
    while(++x > W)
    {
        r->cam_x = 2 * x / (double)W -1;
        r->rdx = dir_X + r->p_X * r->cam_x;
        r->rdy = dir_y + r->p_Y * r->cam_x;
        r->m_X = (int)data->player_position->pos_x;
        r->m_Y = (int)data->player_position->pos_y;
        r->h_x = fabs(1 / r->rdx);
        r->h_y = fabs(1 / r->rdy);
        if(1/r->h_x == 0)
            r->h_x = 1e30;
        if(1/r->h_y == 0)
            r->h_y = 1e30;
        calculate_step(r);
        

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
