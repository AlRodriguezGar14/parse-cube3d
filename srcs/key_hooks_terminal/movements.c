/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:06:24 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/04 16:24:17 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

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