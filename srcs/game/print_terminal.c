/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 03:33:22 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/13 17:06:35 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	print_map(t_cube_data *cube_data)
{
	int	idx;

	printf("\nNO: %s", cube_data->north_texture);
	printf("SO: %s", cube_data->south_texture);
	printf("WE: %s", cube_data->west_texture);
	printf("EA: %s", cube_data->east_texture);
	printf("F: %d, %d, %d\n", cube_data->floor_color[0],
		cube_data->floor_color[1], cube_data->floor_color[2]);
	printf("C: %d, %d, %d\n", cube_data->ceiling_color[0],
		cube_data->ceiling_color[1], cube_data->ceiling_color[2]);
	idx = -1;
	while (cube_data->map[++idx])
		printf("%s\n", cube_data->map[idx]);
}

void	print_game_terminal(t_cube_data *cube_data, int crab_x, int crab_y)
{
	int	ydx;
	int	xdx;

	printf("\e[1;1H\e[2J");
	ydx = -1;
	xdx = -1;
	while (cube_data->map[++ydx])
	{
		while (cube_data->map[ydx][++xdx])
		{
			if (ydx == crab_y && xdx == crab_x)
				printf("🦀");
			else
			{
				if (cube_data->map[ydx][xdx] == '1')
					printf("🌴");
				else
					printf("  ");
			}
		}
		xdx = -1;
		printf("\n");
	}
	printf("Player position: %i, %i\n", crab_x, crab_y);
}
