/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:25:12 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 02:50:59 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int	destroy_window(void *param)
{
	int			idx;
	t_cube_data	*cube_data;

	idx = -1;
	cube_data = (t_cube_data *)param;
	mlx_destroy_window(cube_data->mlx.mlx, cube_data->mlx.win);
	free_content(cube_data);
	idx = -1;
	while (++idx < 5)
	{
		if (cube_data->textures[idx].created == true)
		{
			printf("destroying image %d\n", idx);
			mlx_destroy_image(cube_data->mlx.mlx,
				cube_data->textures[idx].image_charge);
		}
	}
	free(cube_data->textures);
	free(cube_data->mlx.mlx);
	exit(1);
}

int	key_release(int keycode, void *param)
{
	t_cube_data	*cube_data;

	cube_data = (t_cube_data *)param;
	if (keycode == D)
		cube_data->move.mright = 0;
	if (keycode == A)
		cube_data->move.mleft = 0;
	if (keycode == W)
		cube_data->move.mup = 0;
	if (keycode == S)
		cube_data->move.mback = 0;
	if (keycode == LEFT)
		cube_data->move.rright = 0;
	if (keycode == RIGHT)
		cube_data->move.rleft = 0;
	return (0);
}

int	key_pressed(int keycode, void *param)
{
	t_cube_data	*cube_data;

	cube_data = (t_cube_data *)param;
	if (keycode == D)
		cube_data->move.mright = 1;
	if (keycode == A)
		cube_data->move.mleft = 1;
	if (keycode == W)
		cube_data->move.mup = 1;
	if (keycode == S)
		cube_data->move.mback = 1;
	if (keycode == LEFT)
		cube_data->move.rright = 1;
	if (keycode == RIGHT)
		cube_data->move.rleft = 1;
	if (keycode == ESC)
	{
		printf("ESC pressed\n");
		return (destroy_window(cube_data));
	}
	return (0);
}
