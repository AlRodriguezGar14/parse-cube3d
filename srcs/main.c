/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:23:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/04 13:47:36 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsecube.h"

void hooks(t_cube_data *game)
{
	mlx_hook(game->mlx->win, 2, 1L << 0, key_pressed, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, 17, 1L << 17, destroy_window, game);
}

// TODO: REMOVE WHEN IT'S NOT NEEDED ANYMORE
void    print_map(t_cube_data *cube_data)
{
	// PRINT THE STRUCTURE
	printf("\nNO: %s", cube_data->north_texture);
	printf("SO: %s", cube_data->south_texture);
	printf("WE: %s", cube_data->west_texture);
	printf("EA: %s", cube_data->east_texture);
	printf("F: %d, %d, %d\n", cube_data->floor_color[0], cube_data->floor_color[1], cube_data->floor_color[2]);
	printf("C: %d, %d, %d\n", cube_data->ceiling_color[0], cube_data->ceiling_color[1], cube_data->ceiling_color[2]);
	int idx = 0;
	while (cube_data->map[++idx])
		printf("%s\n", cube_data->map[idx]);

}

void	print_game_terminal(t_cube_data *cube_data)
{
	printf("\e[1;1H\e[2J");
	int ydx = -1;
	int xdx = -1;
	while (cube_data->map[++ydx])
	{
		while (cube_data->map[ydx][++xdx])
		{
			if (ydx == cube_data->player_position->y && xdx == cube_data->player_position->x)
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
}


void	init_mlx(t_mlx *mlx ,t_cube_data *cube_data)
{
	mlx->mlx = mlx_init();
	// TODO: Update max_x to a fixed value
	ft_strlen_map(cube_data->map,cube_data);
	printf("x%i y%i\n",cube_data->max_x,cube_data->max_y);
	mlx->win = mlx_new_window(mlx->mlx, cube_data->max_x * TILE_SIZE, cube_data->max_y * TILE_SIZE, "Cub3D");
	// mlx->win = mlx_new_window(mlx->mlx, 640, 320, "Cub3D");
	
}



int	main(int argc, char **argv)
{
	t_cube_data         cube_data;
	t_player_position	player_position;
	t_mlx				mlx;

	printf("\e[1;1H\e[2J");
	if (argc != 2 || validate_extension(argv[1]))
		return (1);
	printf("Parsing the file...\n");
	ft_bzero(&cube_data, sizeof(t_cube_data));
	ft_bzero(&player_position, sizeof(t_player_position));
	ft_bzero(&mlx, sizeof(t_mlx));
	// TODO: IMPROVE THE PARSING WITH MORE EDGE CASES FOR INPUT ERRORS
	if (read_file(argv[1], &cube_data))
		return (1);
	print_map(&cube_data);
	replace_tabs_with_spaces(&cube_data.map); // this is a way to "justify" the map and avoid spacing issues
	if (validate_file(&cube_data))
		return (printf("Invalid input. Cleanup and exit\n"), 1);
	if (validate_map(&cube_data, &player_position))
		return (printf("Invalid map. Cleanup and exit\n"), 1);
 	 cube_data.textures=(t_image_info *)ft_calloc(sizeof(t_image_info),5);
	 cube_data.r=ft_calloc(sizeof(t_ray),1);
    if(!cube_data.textures)
        exit(0);
	cube_data.player_position = &player_position;
	cube_data.mlx = &mlx;
	ft_bzero(&cube_data.move, sizeof(t_move));
	init_mlx(&mlx, &cube_data);
	load_textures(&cube_data);
	init_player(&cube_data);
	//init_ray(&cube_data);
	paint_map(&cube_data);
	ray(&cube_data);

	t_image_info *img;
	img = &cube_data.textures[4];
	mlx_put_image_to_window(mlx.mlx, mlx.win, img->image_charge, 0, 0);
	//print_c_f(&cube_data);
//	raycasting(&cube_data);
	//mlx_hook(mlx.win,2,1,key_pressed,&cube_data);
	//mlx_loop_hook(cube_data.mlx->mlx,&routine,&cube_data);
	hooks(&cube_data);
	mlx_loop(mlx.mlx);


	// TODO: FREE THE MEMORY

	return (0);
}
