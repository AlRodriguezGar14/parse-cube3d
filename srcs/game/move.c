/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/05 01:47:02 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

void m_rotate(t_cube_data *d, bool flag)
{
	if (flag)
	{
		d->player_position->angle += ROTATION_SPEED;
		if (d->player_position->angle > 2 * M_PI)
			d->player_position->angle -= 2 * M_PI;
	}
	else
	{
		d->player_position->angle -= ROTATION_SPEED;
		if (d->player_position->angle < 0)
			d->player_position->angle += 2 * M_PI;
	}
}

void	move_player(t_cube_data *mlx, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = floor(mlx->player_position->pos_x + move_x);
	new_y = floor(mlx->player_position->pos_y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (map_grid_x < 0 || map_grid_x >= mlx->max_x || \
	map_grid_y < 0 || map_grid_y >= mlx->max_y)
		return ;
	if (mlx->map[map_grid_y][map_grid_x] != '1' )
	{

		printf("new_x: %d, new_y: %d\n", new_x, new_y);
		printf("map_grid_x: %d, map_grid_y: %d\n", map_grid_x, map_grid_y);
		mlx->player_position->pos_x = new_x;
		mlx->player_position->pos_y = new_y;
	}
}

int	moves(t_cube_data *d)
{
	double move_x;
	double move_y;
	move_x = 0;
	move_y = 0;
	
	if(d->move.rleft)
		m_rotate(d, false);
	if(d->move.rright)
		m_rotate(d, true);
	if (d->move.mup)
	{
		printf("up\n");
		move_x = cos(d->player_position->angle) * PLAYER_SPEED;
		move_y = sin(d->player_position->angle) * PLAYER_SPEED;
	}
	if(d->move.mback)
	{
		move_x = -cos(d->player_position->angle) * PLAYER_SPEED;
		move_y = -sin(d->player_position->angle) * PLAYER_SPEED;
	}
	if(d->move.mleft)
	{
		move_x = sin(d->player_position->angle) * PLAYER_SPEED;
		move_y = -cos(d->player_position->angle) * PLAYER_SPEED;
	}
	if(d->move.mright)
	{
		move_x = -cos(d->player_position->angle) * PLAYER_SPEED;
		move_y = -sin(d->player_position->angle) * PLAYER_SPEED;
	}
	if (d->move.mup || d->move.mback || d->move.mleft || d->move.mright)
	{
		printf("me muevo\n");
		move_player(d, move_x, move_y);
	}
	
	return (0);
}