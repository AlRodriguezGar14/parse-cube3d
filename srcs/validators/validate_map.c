/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 04:52:25 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/03 05:51:42 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

int validate_top_bottom(char *line)
{
	int idx;

	idx = -1;
	while (line[++idx] && line[idx] != '\n')
	{
		if (!(line[idx] == ' ' || line[idx] == '1'))
			return (ft_printf("Invalid map top || bottom:\n\t%s\n", line), 1);
	}
	return (0);
}

void    set_initial_position(t_player_position *player_position, int x, int y, char orientation)
{
	player_position->x = x;
	player_position->y = y;
	player_position->orientation = orientation;
	printf("Start position: %d, %d, %c\n", player_position->x, player_position->y, player_position->orientation);
}

int validate_neighbors(char **map, int x, int y)
{
	if (map[y][x] && ft_strchr("0NSWE", map[y][x]))
	{
		if (map[y-1][x] && map[y-1][x] == ' ')
			return (ft_printf("Invalid map line. Not closed:\n\t%s\n\t%s <-\n", map[y - 1], map[y]), 1);
		if (map[y][x-1] && map[y][x-1] == ' ')
			return (ft_printf("Invalid map line. Not closed:\n\t%s\n", map[y]), 1);
		if (map[y+1][x] && map[y+1][x] == ' ')
			return (ft_printf("Invalid map line. Not closed:\n\t%s <-\n\t%s\n", map[y], map[y+1]), 1);
		if (map[y][x+1] && map[y][x+1] == ' ')
			return (ft_printf("Invalid map line: %s\n", map[y]), 1);
	}
	return (0);
}

int validate_line(char **map, int y, t_player_position *player_position)
{
	int x;
	char *line;

	x = -1;
	line = map[y];
	while (line[++x] && ft_isspace(line[x]))
		;
	if (line[x] != '1' || line[ft_strlen(line) - 1] != '1')
		return (ft_printf("Invalid map line:\n\t%s\n", line), 1);
	while (line[++x])
	{
		if (!ft_strchr(" 01", line[x]))
		{
			if (ft_strchr("NSWE", line[x]))
			{
				if (player_position->orientation)
					return (ft_printf("Multiple start positions\n"), 1);
				set_initial_position(player_position, x, y, line[x]);
			}
			else
				return (ft_printf("Invalid map line:\n\t%s\n", line), 1);
		}
		if (validate_neighbors(map, x, y))
			return (1);
	}
	return (0);
}

int validate_map(t_cube_data *cube_data, t_player_position *player_position)
{
	int idx;
	int max_y;

	max_y = double_pointer_len(cube_data->map);
	idx = -1;
	if (max_y <= 0)
		return (ft_printf("Invalid map y\n"), 1);
	while (cube_data->map[++idx])
	{
		if (ft_strlen(cube_data->map[idx]) <= 0)
			return (ft_printf("Invalid map x\n"), 1);
		if ((idx == 0 || idx == max_y - 1) && validate_top_bottom(cube_data->map[idx]))
			return (1);
		if (validate_line(cube_data->map, idx, player_position))
			return (1);
	}
	return (0);
}
