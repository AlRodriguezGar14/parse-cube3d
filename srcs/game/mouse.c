/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:04:25 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	mouse_move(int x, int y, t_cube_data *game)
{
	int	screen_third;
	int	second_third;

	(void)y;
	screen_third = WIDTH / 3;
	second_third = 2 * screen_third;
	if (game->mouse.x == 0 && game->mouse.prev_y == 0)
	{
		game->mouse.prev_x = x;
		game->mouse.prev_y = y;
	}
	game->mouse.x = x;
	game->mouse.y = y;
	if (game->mouse.x < screen_third && game->mouse.prev_x > game->mouse.x)
		game->player_position->angle += 0.03;
	else if (game->mouse.x > second_third && game->mouse.prev_x < game->mouse.x)
		game->player_position->angle -= 0.03;
	game->mouse.prev_x = game->mouse.x;
	game->mouse.prev_y = game->mouse.y;
	return (0);
}
