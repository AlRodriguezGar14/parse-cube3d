/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:17:42 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/19 23:03:52 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"
void	my_mlx_pixel_put(t_image_info *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addres + (y * data->line_s + x * (data->bpp / 8));
	*((unsigned int *)dst) = color;
}
int	rgb(int r, int g, int b)
{
		return (r << 16 | g << 8 | b);
}
int	aux_p(t_image_info *img, int x, int y, int color)
{
	int	z;

	z = H / 2;
	if (y >= H / 2)
		z = H;
	while (x++ < W)
	{
		my_mlx_pixel_put(img, x, y, color);
		if (x == W)
		{
			if (++y == z)
				break ;
			x = 0;
		}
	}
	return (y);
}
void print_c_f(t_cube_data *data)
{
	int c[3];
	int i;
	int x;
	int y;
	
	y = 0;
	x = 0;
	
	i =-1;
	while(++i < 3)
		c[i]=data->ceiling_color[i];
    data->textures->pxlc = rgb(c[0],c[1],c[2]);
	i = -1;
	while (++i < 3)
		c[i]=data->floor_color[i];
    data->textures->pxlf = rgb(c[0],c[1],c[2]);
	i = -1; 
	y = aux_p(&data->textures[4],x,y,data->textures->pxlc);
	x = 0;
	aux_p(&data->textures[4],x,y,data->textures->pxlf);
	mlx_put_image_to_window(data->mlx->mlx,data->mlx->win,data->textures[4].image_charge,0,0);

}
