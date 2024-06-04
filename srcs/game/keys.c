/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:25:12 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/04 13:57:51 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int destroy_window(void *param)
{
	int idx = -1;
	t_cube_data *cube_data;
	cube_data = (t_cube_data *)param;
	mlx_destroy_window(cube_data->mlx->mlx, cube_data->mlx->win);
	while (cube_data->map[++idx])
		free(cube_data->map[idx]);
	free(cube_data->map);
	idx = -1;
	while (++idx < 5)
		mlx_destroy_image(cube_data->mlx->mlx, cube_data->textures[idx].image_charge);
	exit(0);
}

int key_release( int keycode ,void *param)
{
	t_cube_data *cube_data;
	cube_data = (t_cube_data *)param;
	printf("teccla soltada %d\n", keycode);
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

int key_pressed( int keycode ,void *param)
{
	t_cube_data *cube_data;
	cube_data = (t_cube_data *)param;
	printf("teccla pulsada %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(cube_data->mlx->mlx, cube_data->mlx->win);
		exit(0);
	}
	if (keycode == D)
		cube_data->move.mright = 1;
	if (keycode == A)
		cube_data->move.mleft= -1;
	if (keycode == W)
		cube_data->move.mup = 1;
	if (keycode == S)
		cube_data->move.mback = 1;
	if (keycode == LEFT)
		cube_data->move.rright = -1;
	if (keycode == RIGHT)
		cube_data->move.rleft = 1;

	printf("mright %d\n", cube_data->move.mright);
	printf("mleft %d\n", cube_data->move.mleft);
	printf("mup %d\n", cube_data->move.mup);
	printf("mback %d\n", cube_data->move.mback);
	printf("rright %d\n", cube_data->move.rright);
	printf("rleft %d\n", cube_data->move.rleft);

	return (0);
}
