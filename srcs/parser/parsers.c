/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:08:15 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/11 19:29:02 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int    parse_colors(char *line, int color[3])
{
	char *tmp;
	char **colors;
	int idx;

	// TOOD: IMPROVE THE PARSING WITH MORE EDGE CASES FOR INPUT ERRORS
	tmp = ft_strtrim(line, " ");
	colors = ft_split(tmp, ',');
	free(tmp);
	if (double_pointer_len(colors) != 3)
	{
		free_double_pointer(colors);
		return (1);
	}
	color[0] = ft_atoi(colors[0]);
	color[1] = ft_atoi(colors[1]);
	color[2] = ft_atoi(colors[2]);
	idx = -1;
	while (++idx < 3)
	{
		printf("color[%d]: %d\n", idx, color[idx]);
		if (color[idx] < 0 || color[idx] > 255)
			return (free_double_pointer(colors), 1);
	}
	free_double_pointer(colors);
	return (0);
}

void    parse_map(char *line, t_cube_data *cube_data)
{
	int     map_size;
	char    **tmp;
	int     idx;

	if (cube_data->map != NULL)
		map_size = double_pointer_len(cube_data->map);
	else
	{
		printf("initial map size\n");
		map_size = 0;
	}

	printf("line[%d]: %s\n", map_size, line);
	cube_data->max_y = map_size;
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
	int error;

	error = 0;
	if (!line)
		return (1);
	if (!error && ft_strncmp("NO ", line, 3) == 0)
		cube_data->north_texture = line_content(line);
	else if (!error && ft_strncmp("SO ", line, 3) == 0)
		cube_data->south_texture = line_content(line);
	else if (!error && ft_strncmp("WE ", line, 3) == 0)
		cube_data->west_texture = line_content(line);
	else if (!error && ft_strncmp("EA ", line, 3) == 0)
		cube_data->east_texture = line_content(line);
	else if (!error && ft_strncmp("F ", line, 2) == 0)
		error = parse_colors(line + 1, cube_data->floor_color);
	else if (!error && ft_strncmp("C ", line, 2) == 0)
		error = parse_colors(line + 1, cube_data->ceiling_color);
	else
		parse_map(line, cube_data);
	if (error)
	{
		printf("Error parsing; wrong content\n");
		free(line);
		free_content(cube_data);
		exit(1);
	}
	// TODO: CHECK IF THE PATHS ARE VALID
	return (0);
}
