/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:55:36 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

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

int	get_pixel_color(int x, int y, t_image_info *img)
{
	char	*dst;

	dst = img->addres + (y * img->line_s + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int	get_texture_color(t_image_info *texture, int tex_x, int tex_y)
{
	int				bytes_per_pixel;
	int				offset;
	unsigned char	*pixel;
	int				color;

	if (tex_x < 0 || tex_x >= TEXT_SIZE || tex_y < 0 || tex_y >= TEXT_SIZE)
		return (0);
	bytes_per_pixel = texture->bpp / 8;
	offset = (tex_y * texture->line_s) + (tex_x * bytes_per_pixel);
	pixel = (unsigned char *)(texture->addres + offset);
	color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
	return (color);
}
