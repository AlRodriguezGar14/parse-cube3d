/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:36 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/12 03:13:55 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

t_image_info	*get_texture(t_cube_data *data, int side)
{
	t_image_info	*texture;

	if (side == 0)
	{
		if (data->r.ray_dir_x > 0)
			texture = &data->textures[2];
		else
			texture = &data->textures[0];
	}
	else
	{
		if (data->r.ray_dir_y > 0)
			texture = &data->textures[3];
		else
			texture = &data->textures[1];
	}
	return (texture);
}

int	get_texture_color(t_image_info *texture, int tex_x, int tex_y)
{
	int				bytes_per_pixel;
	int				offset;
	unsigned char	*pixel;
	int				color;

	if (tex_x < 0 || tex_x >= 300 || tex_y < 0 || tex_y >= 300)
		return (0);
	bytes_per_pixel = texture->bpp / 8;
	offset = (tex_y * texture->line_s) + (tex_x * bytes_per_pixel);
	pixel = (unsigned char *)(texture->addres + offset);
	color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
	return (color);
}
