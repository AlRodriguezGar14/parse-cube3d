/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:23:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/03 01:35:18 by alberrod         ###   ########.fr       */
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

void	print_game_terminal(t_cube_data cube_data)
{
	printf("\e[1;1H\e[2J");
	printf("NO: %s\n", cube_data.north_texture);
}


void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 800, 600, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, 800, 600);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
}

int	main(int argc, char **argv)
{
	t_cube_data         cube_data;
	t_start_position	start_position;
	t_mlx				mlx;

	if (argc != 2 || validate_extension(argv[1]))
		return (1);
	ft_memset(&cube_data, 0, sizeof(t_cube_data));
	ft_memset(&start_position, 0, sizeof(t_start_position));
	ft_memset(&mlx, 0, sizeof(t_mlx));

	// TODO: IMPROVE THE PARSING WITH MORE EDGE CASES FOR INPUT ERRORS
	read_file(argv[1], &cube_data);
	replace_tabs_with_spaces(&cube_data.map); // this is a way to "justify" the map and avoid spacing issues
	if (validate_file(&cube_data))
		return (printf("Invalid input. Cleanup and exit\n"), 1);
	if (validate_map(&cube_data, &start_position))
		return (printf("Invalid map. Cleanup and exit\n"), 1);

	print_map(cube_data);
	init_mlx(&mlx);
	mlx_loop(mlx.mlx);

	// print_game_terminal(cube_data);

	// TODO: FREE THE MEMORY

	return (0);
}
