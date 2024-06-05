/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:17:42 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:42 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

t_image_info *renew_image(t_cube_data *data)
{
	load_textures_helper(data, NULL, 4);
	get_addres_helper(data, 4);

	return (&data->textures[4]);
}


void	my_mlx_pixel_put(t_image_info *data, int x, int y, int color, int width, int height)
{
	char	*dst;

	if (!data->addres)
		return ;

	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		dst = data->addres + (y * data->line_s + x * (data->bpp / 8));
		*((unsigned int *)dst) = color;
	}
}

int	rgb(int r, int g, int b)
{
		return (r << 16 | g << 8 | b);
}
//
//int	aux_p(t_image_info *img, int x, int y, int color)
//{
//	int	z;
//
//	z = H_S / 2;
//	if (y >= H_S / 2)
//		z = H_S;
//	while (x++ < W_S)
//	{
//		my_mlx_pixel_put(img, x, y, color);
//		if (x == W_S)
//		{
//			if (++y == z)
//				break ;
//			x = 0;
//		}
//	}
//	return (y);
//}
//void print_c_f(t_cube_data *data)
//{
//	int c[3];
//	int i;
//	int x;
//	int y;
//
//	y = 0;
//	x = 0;
//
//	i =-1;
//	while(++i < 3)
//		c[i]=data->ceiling_color[i];
//    data->textures->pxlc = rgb(c[0],c[1],c[2]);
//	i = -1;
//	while (++i < 3)
//		c[i]=data->floor_color[i];
//    data->textures->pxlf = rgb(c[0],c[1],c[2]);
//	i = -1;
//	y = aux_p(&data->textures[4],x,y,data->textures->pxlc);
//	x = 0;
//	aux_p(&data->textures[4],x,y,data->textures->pxlf);
//	mlx_put_image_to_window(data->mlx->mlx,data->mlx->win,data->textures[4].image_charge,0,0);
//
//}
