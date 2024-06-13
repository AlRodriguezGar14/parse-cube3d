/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:23:16 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	get_plyr_pos(t_cube_data *data)
{
	data->player_position->pos_x = data->player_position->x * TILE_SIZE
		+ TILE_SIZE / 2;
	data->player_position->pos_y = data->player_position->y * TILE_SIZE
		+ TILE_SIZE / 2;
	moves(data);
}

void	ft_strlen_map(char **map, t_cube_data *data)
{
	int	i;

	i = 0;
	data->max_x = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > data->max_x)
			data->max_x = ft_strlen(map[i]);
		i++;
	}
}
