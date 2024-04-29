/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:23:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/29 16:22:23 by alberrod         ###   ########.fr       */
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

int double_pointer_len(char **ptr)
{
	int len;

	len = 0;
	while (ptr[len])
		len++;
	return (len);
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
	tmp[idx] = ft_strdup(line);
	free(cube_data->map);
	cube_data->map = tmp;
}

int parse_line(char *line, t_cube_data *cube_data)
{
	if (!line)
		return (1);
	if (ft_strncmp("NO", line, 2) == 0)
		cube_data->north_texture = clean_line(line);
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
		parse_map(line, cube_data);
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

void replace_tabs_with_spaces(char ***map)
{
    int idx;
    int idx2;
    char *new_line;
    char *tmp;
	char *to_append;

    idx = -1;
    while ((*map)[++idx])
    {
        new_line = ft_strdup("");
        idx2 = -1;
        while ((*map)[idx][++idx2])
        {
            if ((*map)[idx][idx2] == '\t')
				to_append = ft_strdup("    ");
            else
				to_append = ft_sprintf("%c", (*map)[idx][idx2]);
			tmp = ft_strdup(new_line);
			free(new_line);
			new_line = ft_sprintf("%s%s", tmp, to_append);
			free(tmp);
			free(to_append);
        }
        free((*map)[idx]);
        (*map)[idx] = new_line;
    }
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
	replace_tabs_with_spaces(&cube_data.map); // this is a way to "justify" the map and avoid spacing issues

	// PRINT THE STRUCTURE
	printf("\nNO: %s", cube_data.north_texture);
	printf("SO: %s", cube_data.south_texture);
	printf("WE: %s", cube_data.west_texture);
	printf("EA: %s", cube_data.east_texture);
	printf("F: %d, %d, %d\n", cube_data.floor_color[0], cube_data.floor_color[1], cube_data.floor_color[2]);
	printf("C: %d, %d, %d\n", cube_data.ceiling_color[0], cube_data.ceiling_color[1], cube_data.ceiling_color[2]);
	int idx = -1;
	while (cube_data.map[++idx])
		printf("%s", cube_data.map[idx]);

	// TODO: FREE THE MEMORY
	return (0);
}
