/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:36 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/10 13:49:23 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

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
int get_texture_color(t_image_info *texture, int tex_x, int tex_y) 
{
    if (tex_x < 0 || tex_x >= 300 || tex_y < 0 || tex_y >= 300)
        return 0; // Devuelve un color por defecto o de error si las coordenadas están fuera de rango
    int bytes_per_pixel = texture->bpp / 8;
    int offset = (tex_y * texture->line_s) + (tex_x * bytes_per_pixel);
    unsigned char *pixel = (unsigned char *)(texture->addres + offset);
    int color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0]; // Asume formato RGB
    return color;
}

