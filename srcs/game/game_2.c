/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:36 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/19 23:00:15 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int get_pixel_color(t_image_info *img, int x, int y)
{
	int color;
	
	if( x >= 0 && x < TILE_SIZE && y >= 0 && y < TILE_SIZE)
		return(*(int *)(img +(4 * TILE_SIZE * y) + (4 * x)));
	return (0x0);
}
t_image_info *select_texture(t_cube_data *data, int side)
{
	t_image_info *img;
	
	if (side == 0)
	{
		if (data->r->rdx > 0)
			img = &data->textures[0];
		else
			img = &data->textures[1];
	}
	else
	{
		if (data->r->rdy > 0)
			img = &data->textures[2];
		else
			img = &data->textures[3];
	}
	return img;
}
int ray_pos(t_ray *r, int side)
{
	double wall_x;
	
	if (side == 0)
		wall_x = r->p_Y + r->p_wall_dist * r->rdy;
	else
		wall_x = r->p_X + r->p_wall_dist * r->rdx;
	wall_x -= floor(wall_x);
	return (int)(wall_x * (double)TILE_SIZE);
}

void print_ray(t_cube_data *data, int draw[2], int x, int side)
{
	t_ray *r;
	t_image_info *img;
	int y;
	int text_y;
	int color;

	img = NULL;
	r = data->r;
	r->tesx_x = ray_pos(r, side);
	if(side == 0 && r->rdx > 0)
		r->tesx_x= TILE_SIZE - r->tesx_x - 1;
	if(side == 1 && r->rdy < 0)
		r->tesx_x= TILE_SIZE - r->tesx_x - 1;
	y = draw[0];
	while(y++ < draw[1])
	{
		text_y = (int)r->tex_pos & (TILE_SIZE - 1);
		r->tex_pos += r->step;
		img = select_texture(data, side);
		color = get_pixel_color(img, r->tesx_x, text_y);
		my_mlx_pixel_put(&data->textures[4], x, y, color);
	}
}
