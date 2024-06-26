/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:17:42 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_image_info	*renew_image(t_cube_data *data)
{
	load_textures_helper(data, NULL, 4);
	get_addres_helper(data, 4);
	return (&data->textures[4]);
}

void	my_mlx_pixel_put(t_image_info *data, int x, int y, int color)
{
	char	*dst;

	if (!data->addres)
		return ;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addres + (y * data->line_s + x * (data->bpp / 8));
		*((unsigned int *)dst) = color;
	}
}

int	rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
