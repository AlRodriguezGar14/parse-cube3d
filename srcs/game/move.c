/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:26:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/04 15:39:38 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

void move_right(t_cube_data *d, double movespeed)
{
	if (d->map[(int)(d->player_position->x + d->player_position->dir_x * movespeed)][(int)d->player_position->y] == 0)
		d->player_position->x += d->player_position->dir_x * movespeed;
	if (d->map[(int)d->player_position->x][(int)(d->player_position->y + d->player_position->dir_y * movespeed)] == 0)
		d->player_position->y += d->player_position->dir_y * movespeed;
}

int	move(t_cube_data *d)
{
	double	movespeed;
	double	rotspeed;

	movespeed = PLAYER_SPEED;
	rotspeed = ROTATION_SPEED;

	if(d->move.mright)
		move_right(d, movespeed);
	if(d->move.mleft)
		ft_move_left(d, movespeed);
	if(d->move.mup)
		ft_move_up(d, movespeed);
	if(d->move.mback)
		ft_move_back(d, movespeed);
	if(d->move.rright)
		ft_lrotate(d, rotspeed); 
	if (d->move.rleft)
		ft_rrotate(d, rotspeed);

	return (0);
}