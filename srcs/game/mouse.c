/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:04:25 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 10:40:00 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int	mouse_move(int x, int y, t_cube_data *game)
{
	(void)y;
	(void)x;
	if (game->mouse.x == 0 && game->mouse.prev_y == 0)
	{
		game->mouse.prev_x = x;
		game->mouse.prev_y = y;
	}
	game->mouse.x = x;
	game->mouse.y = y;
	if (game->mouse.x > game->mouse.prev_x)
	{
		m_rotate(game, true);
	}
	else if (game->mouse.x < game->mouse.prev_x)
	{
		m_rotate(game, false);
	}
	game->mouse.prev_x = game->mouse.x;
	game->mouse.prev_y = game->mouse.y;
	return (0);
}
