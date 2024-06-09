/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:36 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/08 23:48:27 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

/* void put_wall(t_cube_data *data, int draw_end, int draw_start , t_image_info *texture)
{
	int color;
	double step;
	int tex_pos;
	int color;
	int y;
	int texy;


	step = 1.0 * 300 / texture->line_s;

} */

t_image_info *get_texture(t_cube_data *data, int side)
{
	t_image_info *texture;

	if (side == 0) // Vertical wall
	{
		if (data->r.ray_dir_x > 0)
			texture = &data->textures[2]; // West
		else
			texture = &data->textures[0]; // East
	}
	else // Horizontal wall
	{
		if (data->r.ray_dir_y > 0)
			texture = &data->textures[3]; // North
		else
			texture = &data->textures[1]; // South
	}
	return (texture);
}

// function that returns the color of the pixel in the texture
int get_texture_color(t_image_info *texture, int x, int y)
{
	if (x < 0 || y < 0 || x >= texture->line_s || y >= texture->line_s)
		return (0);
	char *dst;

	dst = texture->addres + (y * texture->line_s + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}
