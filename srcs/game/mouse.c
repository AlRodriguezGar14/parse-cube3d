/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:04:25 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 11:51:38 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int	mouse_move(int x, int y, t_cube_data *game)
{
	(void)x;
	double diff_treshold = 0.5;
	
	if (game->mouse.x == 0 && game->mouse.prev_y == 0)
	{
		game->mouse.prev_x = x;
		game->mouse.prev_y = y;
	}
	game->mouse.x = x;
	game->mouse.y = y;
	if (game->mouse.x > game->mouse.prev_x + diff_treshold)
	{
		game->player_position->angle -= 0.03;
	}
	else if (game->mouse.x < game->mouse.prev_x - diff_treshold)
	{
		game->player_position->angle += 0.03;
	}

	game->mouse.prev_x = game->mouse.x;
	game->mouse.prev_y = game->mouse.y;
	return (0);
}
