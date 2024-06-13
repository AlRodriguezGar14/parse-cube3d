/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 02:24:22 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	set_initial_position(t_player_position *player_position, int x, int y,
		char orientation)
{
	player_position->x = x;
	player_position->y = y;
	player_position->orientation = orientation;
	printf("Start position: %d, %d, %c\n", player_position->x,
		player_position->y, player_position->orientation);
}
