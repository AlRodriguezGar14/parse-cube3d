/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:23:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/29 04:21:53 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

int validate_extension(char *file)
{
	int len;

	len = ft_strlen(file);
	if (len < 4)
		return (ft_printf("Invalid file name\n"), 1);
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (ft_printf("Wrong file format\n"), 1);
	return (0);
}

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char    *clean_line(char *line)
{
	int idx;

	idx = 2;

	while (line[++idx])
	{
		if (!ft_isspace(line[idx]))
			break;
	}
	return (ft_substr(line, idx, ft_strlen(line) - idx));
}

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

int parse_line(char *line, t_cube_data *cube_data)
{
	if (!line)
		return (0);
	if (ft_strncmp("NO", line, 2) == 0)
	{
		printf("NO: %s\n", line);
		cube_data->north_texture = clean_line(line);
	}
	else if (ft_strncmp("SO", line, 2) == 0)
		cube_data->south_texture = clean_line(line);
	else if (ft_strncmp("WE", line, 2) == 0)
		cube_data->west_texture = clean_line(line);
	else if (ft_strncmp("EA", line, 2) == 0)
		cube_data->east_texture = clean_line(line);
	else if (ft_strncmp("F", line, 1) == 0)
		parse_colors(line + 1, cube_data->floor_color);
	else if (ft_strncmp("C", line, 1) == 0)
		parse_colors(line + 1, cube_data->ceiling_color);
	else
		return (ft_printf("Parse the map\n"));
	return (0);
}
int read_file(char *file, t_cube_data *cube_data)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Can't read the file\n"), 1);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
//		ft_printf("%s", line);
		if (line[0] == '\n' || line[0] == '\0')
			continue;
		parse_line(line, cube_data);
		free(line);
	}
//	free(line);
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube_data	cube_data;

	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (validate_extension(argv[1]))
		return (1);
	ft_memset(&cube_data, 0, sizeof(t_cube_data));

	// TODO: IMPROVE THE PARSING WITH MORE EDGE CASES FOR INPUT ERRORS
	// THIS IS JUST A "IS WORKING" EXAMPLE
	read_file(argv[1], &cube_data);
	printf("\nNO: %s", cube_data.north_texture);
	printf("SO: %s", cube_data.south_texture);
	printf("WE: %s", cube_data.west_texture);
	printf("EA: %s", cube_data.east_texture);
	printf("F: %d, %d, %d\n", cube_data.floor_color[0], cube_data.floor_color[1], cube_data.floor_color[2]);
	printf("C: %d, %d, %d\n", cube_data.ceiling_color[0], cube_data.ceiling_color[1], cube_data.ceiling_color[2]);
	return (0);
}
