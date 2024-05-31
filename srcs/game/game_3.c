/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:39:31 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/23 18:42:50 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"


int get_pixel_color(int x, int y, t_image_info *img)
{
	char *dst;

	dst = img->addres + (y * img->line_s + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}
double	get_pixel_pos(t_image_info	*texture, t_cube_data *data)
{
	double	pos;

	if (data->r->flag == 1)
		pos = (int)fmodf((data->r->horiz_x * \
		(texture->line_s / TILE_SIZE)), texture->line_s);
	else
		pos = (int)fmodf((data->r->vert_y * \
		(texture->line_s / TILE_SIZE)), texture->line_s);
	return (pos);
}