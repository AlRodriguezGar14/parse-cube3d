/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 02:51:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/12 03:06:18 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

t_pos	calculate_new_position(t_cube_data *data, double move_x, double move_y)
{
	double	module_x;
	double	module_y;
	t_pos	new_pos;

	new_pos.x = data->r.pos_x + move_x;
	new_pos.y = data->r.pos_y + move_y;
	module_x = new_pos.x - (int)new_pos.x;
	module_y = new_pos.y - (int)new_pos.y;
	if ((int)new_pos.y == 0)
		(new_pos.y)++;
	if ((int)new_pos.y - 1 >= 0 && data->map[(int)new_pos.y
			- 1][(int)new_pos.x] == '1' && module_y < 0.15)
		return ((t_pos){.x = data->r.pos_x, .y = data->r.pos_y});
	if ((int)new_pos.y + 1 < data->max_y && data->map[(int)new_pos.y
			+ 1][(int)new_pos.x] == '1' && module_y > 0.85)
		return ((t_pos){.x = data->r.pos_x, .y = data->r.pos_y});
	if ((int)new_pos.x - 1 >= 0 && data->map[(int)new_pos.y][(int)new_pos.x
		- 1] == '1' && module_x < 0.15)
		return ((t_pos){.x = data->r.pos_x, .y = data->r.pos_y});
	if ((int)new_pos.x + 1 < data->max_x
		&& data->map[(int)new_pos.y][(int)new_pos.x + 1] == '1'
		&& module_x > 0.85)
		return ((t_pos){.x = data->r.pos_x, .y = data->r.pos_y});
	return (new_pos);
}

void	update_player_position(t_cube_data *data, double new_pos_x,
		double new_pos_y)
{
	if (new_pos_x >= 0 && new_pos_x < data->max_x && new_pos_y >= 0
		&& new_pos_y < data->max_y)
	{
		data->r.pos_x = new_pos_x;
		data->r.pos_y = new_pos_y;
	}
	printf("x%i y%i\n", (int)data->r.pos_x, (int)data->r.pos_y);
}
