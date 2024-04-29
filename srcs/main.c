/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:23:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/29 03:43:05 by alberrod         ###   ########.fr       */
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

int read_file(char *file, t_cube_data *cube_data)
{
	int fd;
	char *line;
	(void)cube_data;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Can't read the file\n"), 1);
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
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
	read_file(argv[1], &cube_data);
	return (0);
}
