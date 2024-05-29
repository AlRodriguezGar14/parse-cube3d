/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:36 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/25 01:56:06 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

float	get_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
t_image_info *get_img(t_cube_data *data, int flag)
{
	if (flag == 0)
		{
			if (data->r->ray_ngl > M_PI / 2 && data->r->ray_ngl < 3 * M_PI / 2)
				return (&data->textures[0]);
			else
				return (&data->textures[2]);
		}
	else
		{
			if(data->r->ray_ngl > 0 && data->r->ray_ngl < M_PI)
				return (&data->textures[1]);
			else
				return (&data->textures[3]);
		}
	}

int draw_wall(t_cube_data *data, int ray, double top_pxl, double bot_pxl, double wall)
{
	int color;
	t_image_info *img;
	int pos_x;
	int pos_y;
	double fctr;
	
	data->r->ray_ngl = get_angle(data->r->ray_ngl);
	img = get_img(data, data->r->flag);
	fctr = (double)img->line_s / wall;
	pos_x = get_pixel_pos(img, data); 
	pos_y = (top_pxl - (H_S / 2) + (wall / 2)) * fctr;
	if (pos_y < 0)
		pos_y = 0;
	
	while (top_pxl < bot_pxl)
	{	
		my_mlx_pixel_put(&data->textures[4], data->r->index,top_pxl,color);
		top_pxl++;
	}
}
void render (t_cube_data *data , int ray)
{
	double wall;
	double bot_pxl;
	double top_pxl;

	data->r->distance *= cos(data->r->ray_ngl - data->player_position->angle);
	wall = (TILE_SIZE / data->r->distance) * (W_S / 2) / tan(FOV / 2);
	top_pxl = (H_S / 2) - (wall / 2);
	bot_pxl = (H_S/ 2) + (wall / 2);
	if (bot_pxl > H_S)
		bot_pxl = H_S;
	if (top_pxl < 0)
		top_pxl = 0;
	draw_wall(data, ray, top_pxl, bot_pxl, wall);
	
}
void raycasting(t_cube_data *data)
{
	double intersection_x;
	double intersection_y;
	double ray;
	
	ray = 0;
	
	data->r->ray_ngl = data->player_position->angle - (FOV / 2);
	
	while(ray < W)
	{
		data->r->flag = 0;
		intersection_y = get_y_inter(data, data->r->ray_ngl);
		intersection_x = get_x_inter(data, data->r->ray_ngl);
		if (intersection_x <= intersection_y)
			data->r->distance = intersection_x;
		else
		{
			data->r->distance = intersection_y;
			data->r->flag = 1;
		}
		render(data, ray);
		ray++;
		data->r->ray_ngl += (FOV / W_S);
	}
}