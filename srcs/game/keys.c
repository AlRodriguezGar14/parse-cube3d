/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:25:12 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/25 16:35:10 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int key_release( int keycode ,void *param)
{
	t_cube_data *cube_data;
	cube_data = (t_cube_data *)param;
	if (keycode == D || keycode == A)
		cube_data->player_position->left = 0;
	if (keycode == W || keycode == S)
		cube_data->player_position->up = 0;
	if (keycode == LEFT || keycode == RIGHT)
		cube_data->player_position->rotation = 0;
}

int key_pressed( int keycode ,void *param)
{
	t_cube_data *cube_data;
	cube_data = (t_cube_data *)param;
	if (keycode == ESC)
	{
		mlx_destroy_window(cube_data->mlx->mlx, cube_data->mlx->win);
		exit(0);
	}
	if (keycode == D)
		cube_data->player_position->left = 1;
	if (keycode == A)
		cube_data->player_position->left = -1;
	if (keycode == W)
		cube_data->player_position->up = 1;
	if (keycode == S)
		cube_data->player_position->up = -1;
	if (keycode == LEFT)
		cube_data->player_position->rotation = -1;
	if (keycode == RIGHT)
		cube_data->player_position->rotation = 1;
	key_release(keycode, param);
}