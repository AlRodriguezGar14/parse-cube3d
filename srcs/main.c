/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:23:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/13 10:11:16 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsecube.h"

void	hooks(t_cube_data *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, key_pressed, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win, 6, 1L << 6, mouse_move, game);
	//mouse_move is a function that will be called when the mouse is moved
	// mouse_exit is a function that will be called when the mouse exits the window
	mlx_hook(game->mlx.win, 12, 1L << 15, mouse_exit, game);
	mlx_hook(game->mlx.win, 17, 1L << 17, destroy_window, game);
}

void	init_mlx(t_cube_data *cube_data)
{
	cube_data->mlx.mlx = mlx_init();
	ft_strlen_map(cube_data->map, cube_data);
	printf("x%i y%i\n", cube_data->max_x, cube_data->max_y);
	cube_data->mlx.win = mlx_new_window(cube_data->mlx.mlx, WIDTH, HEIGHT,
			"Cub3D");
}

int	validators(t_cube_data *cube_data, t_player_position *player_position)
{
	if (validate_file(cube_data))
	{
		free_content(cube_data);
		return (printf("Invalid input. Cleanup and exit\n"), 1);
	}
	if (validate_map(cube_data, player_position))
	{
		free_content(cube_data);
		return (printf("Invalid map. Cleanup and exit\n"), 1);
	}
	return (0);
}

int	set_game_defaults(t_cube_data *cube_data,
		t_player_position *player_position, int argc, char **argv)
{
	if (argc != 2 || validate_extension(argv[1]))
		return (1);
	if (read_file(argv[1], cube_data) == 1)
		return (1);
	replace_tabs_with_spaces(&cube_data->map, -1);
	if (validators(cube_data, player_position))
		return (1);
	cube_data->textures = (t_image_info *)ft_calloc(sizeof(t_image_info), 5);
	if (!cube_data->textures)
	{
		destroy_window(&cube_data);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube_data			cube_data;
	t_player_position	player_position;

	ft_bzero(&cube_data, sizeof(t_cube_data));
	ft_bzero(&player_position, sizeof(t_player_position));
	if (set_game_defaults(&cube_data, &player_position, argc, argv))
		return (1);
	cube_data.player_position = &player_position;
	ft_bzero(&cube_data.move, sizeof(t_move));
	init_mlx(&cube_data);
	load_textures(&cube_data);
	print_map(&cube_data);
	init_player(&cube_data);
	get_plyr_pos(&cube_data);
	ray(&cube_data);
	hooks(&cube_data);
	mlx_loop_hook(cube_data.mlx.mlx, ray, &cube_data);
	mlx_loop(cube_data.mlx.mlx);
	return (0);
}
