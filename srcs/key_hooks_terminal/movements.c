/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:06:24 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/04 02:06:31 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

void	move_left(t_player_position *player_position)
{
	player_position->x -= 1;
}
void	move_right(t_player_position *player_position)
{
	player_position->x += 1;
}
void	move_down(t_player_position *player_position)
{
	player_position->y += 1;
}
void	move_up(t_player_position *player_position)
{
	player_position->y -= 1;
}