/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/04 17:40:31 by dgomez-m         ###   ########.fr       */
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

	new_x = roundf(mlx->player_position->pos_x + move_x);
	new_y = roundf(mlx->player_position->pos_y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (mlx->map[map_grid_y][map_grid_x] != '1' && \
	(mlx->map[map_grid_y][mlx->player_position->pos_x / TILE_SIZE] != '1' && \
	mlx->map[mlx->player_position->pos_y / TILE_SIZE][map_grid_x] != '1'))
	{
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
		move_x = -sin(d->player_position->angle) * PLAYER_SPEED;
		move_y = cos(d->player_position->angle) * PLAYER_SPEED;
	}
	if(d->move.mback)
	{
		move_x = sin(d->player_position->angle) * PLAYER_SPEED;
		move_y = -cos(d->player_position->angle) * PLAYER_SPEED;
	}
	if(d->move.mleft)
	{
		move_x = cos(d->player_position->angle) * PLAYER_SPEED;
		move_y = sin(d->player_position->angle) * PLAYER_SPEED;
	}
	if(d->move.mright)
	{
		move_x = -cos(d->player_position->angle) * PLAYER_SPEED;
		move_y = -sin(d->player_position->angle) * PLAYER_SPEED;
	}
	if (d->move.mup || d->move.mback || d->move.mleft || d->move.mright)
		move_player(d, move_x, move_y);
	
	return (0);
}