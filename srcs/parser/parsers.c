/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:08:15 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/02 05:09:18 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

void    parse_colors(char *line, int color[3])
{
	char *tmp;
	char **colors;

	// TOOD: IMPROVE THE PARSING WITH MORE EDGE CASES FOR INPUT ERRORS
	tmp = ft_strtrim(line, " ");
	colors = ft_split(tmp, ',');
	color[0] = ft_atoi(colors[0]);
	color[1] = ft_atoi(colors[1]);
	color[2] = ft_atoi(colors[2]);
}

void    parse_map(char *line, t_cube_data *cube_data)
{
	int     map_size;
	char    **tmp;
	int     idx;

	if (cube_data->map != NULL)
		map_size = double_pointer_len(cube_data->map);
	else
		map_size = 0;

	tmp = ft_calloc(sizeof(char *), (map_size + 2));
	idx = -1;
	while (++idx < map_size)
		tmp[idx] = cube_data->map[idx];
	tmp[idx] = ft_strtrim(line, "\n");
	free(cube_data->map);
	cube_data->map = tmp;
}

int parse_line(char *line, t_cube_data *cube_data)
{
	if (!line)
		return (1);
	if (ft_strncmp("NO", line, 2) == 0)
		cube_data->north_texture = line_content(line);
	else if (ft_strncmp("SO", line, 2) == 0)
		cube_data->south_texture = line_content(line);
	else if (ft_strncmp("WE", line, 2) == 0)
		cube_data->west_texture = line_content(line);
	else if (ft_strncmp("EA", line, 2) == 0)
		cube_data->east_texture = line_content(line);
	else if (ft_strncmp("F", line, 1) == 0)
		parse_colors(line + 1, cube_data->floor_color);
	else if (ft_strncmp("C", line, 1) == 0)
		parse_colors(line + 1, cube_data->ceiling_color);
	else
		parse_map(line, cube_data);
	return (0);
}