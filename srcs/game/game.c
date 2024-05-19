/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:02:40 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/19 23:02:00 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"
void wall_distance(t_cube_data *data, t_ray *r, int side, int x)
{
    int l_size;
    int draw[2];
    if (side == 0)
        r->p_wall_dist = (r->m_X - r->p_X + (1 - r->step_x) / 2) / r->rdx;
    else
        r->p_wall_dist = (r->m_Y - r->p_Y + (1 - r->step_y) / 2) / r->rdy;
    l_size = (int)(H / r->p_wall_dist);
    draw[0] = -l_size / 2 + H / 2;
    draw[1] = l_size / 2 + H / 2;
    if (draw[0] < 0)
        draw[0] = 0;
    if (draw[1] >= H)
        draw[1] = H - 1;
    r->step = 1.0 * l_size / W;
    r->tex_pos = (draw[0] - H / 2 + l_size / 2) * r->step;
    print_ray(data, draw, x, side);
    
}

int hit_wall(char **map, t_ray *r)
{
    int hit;
    hit = 0;
    while (hit == 0)
    {
        if (r->s_x < r->s_y)
        {
            r->s_x += r->h_x;
            r->m_X += r->step_x;
            hit = 0;
        }
        else
        {
            r->s_y += r->h_y;
            r->m_Y += r->step_y;
            hit = 1;
        }
        if (map[r->m_Y][r->m_X] == '1')
            hit = 1;
    }
    return hit;
}

void   calculate_step(t_ray *r)
{
    if (r->rdx < 0)
	{
        r->step_x = -1;
        r->s_x = (r->p_X - r->m_X) * r->h_x;
    }
    else
    {
        r->step_x = 1;
        r->s_x = (r->m_X + 1.0 - r->p_X) * r->h_x;
    }
    if (r->rdy < 0)
    {
        r->step_y = -1;
        r->s_y = (r->p_Y - r->m_Y) * r->h_y;
    }
    else
    {
        r->step_y = 1;
        r->s_y = (r->m_Y + 1.0 - r->p_Y) * r->h_y;
    }
}
void raycasting(t_cube_data *data)
{
    t_ray *r;
    double y_inter;
    double x_inter;
    double dir_X;
    double dir_y;
    int side;
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
        side = hit_wall(data->map, r);
        wall_distance(data, r, side, x);

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
