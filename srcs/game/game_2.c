/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:36 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/12 16:00:42 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

t_image_info	*get_texture(t_cube_data *data, int side)
{
	t_image_info	*texture;

	if (side == 0)
	{
		if (data->r.ray_dir_x > 0)
			texture = &data->textures[EAST];
		else
			texture = &data->textures[WEST];
	}
	else
	{
		if (data->r.ray_dir_y > 0)
			texture = &data->textures[NORTH];
		else
			texture = &data->textures[SOUTH];
	}
	return (texture);
}

int	get_texture_color(t_image_info *texture, int tex_x, int tex_y)
{
	int				bytes_per_pixel;
	int				offset;
	unsigned char	*pixel;
	int				color;

	if (tex_x < 0 || tex_x >= 64 || tex_y < 0 || tex_y >= 64)
		return (0);
	bytes_per_pixel = texture->bpp / 8;
	offset = (tex_y * texture->line_s) + (tex_x * bytes_per_pixel);
	pixel = (unsigned char *)(texture->addres + offset);
	color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
	return (color);
}
