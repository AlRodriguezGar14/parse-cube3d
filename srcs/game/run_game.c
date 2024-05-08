/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:52:51 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/07 19:54:22 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

void charge_map(t_cube_data *cube_data)
{
	cube_data->map = malloc(sizeof(char *) * 10);
	cube_data->map[0] = ft_strdup("1111111111111111111111111");
	cube_data->map[1] = ft_strdup("1P00000000110000000000001");
	cube_data->map[2] = ft_strdup("1000000000110000000000001");
	cube_data->map[3] = ft_strdup("1000000000110000000000001");
	cube_data->map[4] = ft_strdup("1000000000110000000000001");
	cube_data->map[5] = ft_strdup("1000000000110000000000001");
	cube_data->map[6] = ft_strdup("1000000000110000000000001");
	cube_data->map[7] = ft_strdup("1000000000110000000000001");
	cube_data->map[8] = ft_strdup("1111111111111111111111111");
	cube_data->map[9] = NULL;
	cube_data->max_y = 9;
	cube_data->player_position = malloc(sizeof(t_player_position));
	cube_data->player_position->x = 1;
	cube_data->player_position->y = 1;
	cube_data->player_position->orientation = 'N';
	
}

void load_textures(t_cube_data *cube_data)
{
	int	x;
	int	y;
	cube_data->north_texture = mlx_xpm_file_to_image(cube_data->mlx->mlx, "textures/1.xpm", &(x), &(y));
	cube_data->south_texture = mlx_xpm_file_to_image(cube_data->mlx->mlx, "textures/2.xpm", &(x), &(y));
	cube_data->west_texture = mlx_xpm_file_to_image(cube_data->mlx->mlx, "textures/3.xpm", &(x), &(y));
	cube_data->east_texture = mlx_xpm_file_to_image(cube_data->mlx->mlx, "textures/4.xpm", &(x), &(y));
}
int exit_game(t_cube_data *cube_data)
{
	free_content(cube_data);
	free_mlx(cube_data->mlx);
	mlx_destroy_window(cube_data->mlx->mlx, cube_data->mlx->win);
	exit(0);
}
