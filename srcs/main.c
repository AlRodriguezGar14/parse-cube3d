/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:23:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/02 05:18:30 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

// TODO: REMOVE WHEN IT'S NOT NEEDED ANYMORE
void    print_map(t_cube_data cube_data)
{
	// PRINT THE STRUCTURE
	printf("\nNO: %s", cube_data.north_texture);
	printf("SO: %s", cube_data.south_texture);
	printf("WE: %s", cube_data.west_texture);
	printf("EA: %s", cube_data.east_texture);
	printf("F: %d, %d, %d\n", cube_data.floor_color[0], cube_data.floor_color[1], cube_data.floor_color[2]);
	printf("C: %d, %d, %d\n", cube_data.ceiling_color[0], cube_data.ceiling_color[1], cube_data.ceiling_color[2]);
	int idx = -1;
	while (cube_data.map[++idx])
		printf("%s\n", cube_data.map[idx]);

}


int	main(int argc, char **argv)
{
	t_cube_data         cube_data;
	t_start_position    start_position;

	if (argc != 2 || validate_extension(argv[1]))
		return (1);
	ft_memset(&cube_data, 0, sizeof(t_cube_data));
	ft_memset(&start_position, 0, sizeof(t_start_position));

	// TODO: IMPROVE THE PARSING WITH MORE EDGE CASES FOR INPUT ERRORS
	read_file(argv[1], &cube_data);
	replace_tabs_with_spaces(&cube_data.map); // this is a way to "justify" the map and avoid spacing issues
	if (validate_file(&cube_data))
		return (printf("Invalid input. Cleanup and exit\n"), 1);
	if (validate_map(&cube_data, &start_position))
		return (printf("Invalid map. Cleanup and exit\n"), 1);

	print_map(cube_data);

	// TODO: FREE THE MEMORY
	return (0);
}
