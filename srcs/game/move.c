/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/12 16:20:15 by alberrod         ###   ########.fr       */
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

void	move_player(t_cube_data *data, double move_x, double move_y)
{
	t_pos	new_pos;

	new_pos = calculate_new_position(data, move_x, move_y);
	update_player_position(data, new_pos.x, new_pos.y);
}

int	do_moves(t_cube_data *d, double move_x, double move_y)
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
		move_player(d, move_x, move_y);
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
	print_game_terminal(d);
	return (0);
}
