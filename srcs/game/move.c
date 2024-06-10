/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/10 23:32:26 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

void	m_rotate(t_cube_data *d, bool flag)
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

static void	move_player(t_cube_data *data, double move_x, double move_y)
{
	double	new_pos_x;
	double	new_pos_y;
	double	module_x;
	double	module_y;

	new_pos_x = data->r.pos_x + move_x;
	new_pos_y = data->r.pos_y + move_y;
	module_x = new_pos_x - (int)new_pos_x;
	module_y = new_pos_y - (int)new_pos_y;
	if (data->map[(int)new_pos_y - 1][(int)new_pos_x] == '1' && module_y < 0.10)
		return ;
	if (data->map[(int)new_pos_y + 1][(int)new_pos_x] == '1' && module_y > 0.90)
		return ;
	if (data->map[(int)new_pos_y][(int)new_pos_x - 1] == '1' && module_x < 0.10)
		return ;
	if (data->map[(int)new_pos_y][(int)new_pos_x + 1] == '1' && module_x > 0.90)
		return ;
	if (new_pos_x >= 0 && new_pos_x < data->max_x && new_pos_y >= 0
		&& new_pos_y < data->max_y)
	{
		data->r.pos_x = new_pos_x;
		data->r.pos_y = new_pos_y;
	}
}

static int	do_moves(t_cube_data *d, double move_x, double move_y)
{
	if (d->move.mup)
	{
		move_x = cos(d->player_position->angle) * PLAYER_SPEED;
		move_y = sin(d->player_position->angle) * PLAYER_SPEED;
	}
	if (d->move.mback)
	{
		move_x = -cos(d->player_position->angle) * PLAYER_SPEED;
		move_y = -sin(d->player_position->angle) * PLAYER_SPEED;
	}
	if (d->move.mleft)
	{
		move_x = cos(d->player_position->angle + M_PI / 2) * PLAYER_SPEED;
		move_y = sin(d->player_position->angle + M_PI / 2) * PLAYER_SPEED;
	}
	if (d->move.mright)
	{
		move_x = cos(d->player_position->angle - M_PI / 2) * PLAYER_SPEED;
		move_y = sin(d->player_position->angle - M_PI / 2) * PLAYER_SPEED;
	}
	if (d->move.mup || d->move.mback || d->move.mleft || d->move.mright)
	{
		move_player(d, move_x, move_y);
	}
	return (0);
}

int	moves(t_cube_data *d)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	if (d->move.rleft)
		m_rotate(d, false);
	if (d->move.rright)
		m_rotate(d, true);
	do_moves(d, move_x, move_y);
	return (0);
}
