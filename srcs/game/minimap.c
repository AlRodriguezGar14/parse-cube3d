/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:23:16 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/05 01:33:23 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"
void get_plyr_pos(t_cube_data *data)
{
	data->player_position->pos_x = data->player_position->x * TILE_SIZE + TILE_SIZE / 2;
	data->player_position->pos_y = data->player_position->y * TILE_SIZE  - TILE_SIZE / 2;
	moves(data);
	printf("x%i y%i\n",data->player_position->pos_x,data->player_position->pos_y);
}


int choose_color(char c)
{
	if (c == '1')
		return (rgb(255, 255, 255));
	if (c == '0')
		return (rgb(0, 0, 0));
	/* if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (rgb(0, 255, 0)); */
	return (0);
}


void ft_strlen_map(char **map , t_cube_data *data )
{
	int i;
	int x;

	i = 1;
	data->max_x = 0;
	while (map[i])
	{
		if(ft_strlen(map[i]) > data->max_x)
			data->max_x = ft_strlen(map[i]);
		i++;
	}
	
}

//void	paint_map(t_cube_data *data)
//{
//	float	x;
//	float	y;
//	int	xs;
//	int	ys;
//	int	color;
//	char c;
//	t_image_info *img;
//	t_player_position *p;
//
//	p= data->player_position;
//	get_plyr_pos(data);
//	img = &data->textures[4];
//
//	y = 0;
//
//	while(++y < TILE_SIZE * data->max_y)
//	{
//		x = -1;
//		while (++x < TILE_SIZE * data->max_x)
//		{
//
//			 xs = x / TILE_SIZE;
//			 ys = y / TILE_SIZE + 1;
//			//ft_strlen_map(data->map, data);
//			 c = data->map[ys][xs];
//			color = choose_color(c);
//			my_mlx_pixel_put(img, x, y, color);
//			if((((x - p->pos_x) * (x - p->pos_x)) + ((y - p->pos_y) * (y - p->pos_y))) <= 100)
//				my_mlx_pixel_put(img, x, y, rgb(255, 127, 0));
//		}
//
//	}
//	// mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, img->image_charge, 0, 0);
//}
