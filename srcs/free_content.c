/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:51:07 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/09 12:14:03 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsecube.h"


void    free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

void	free_content(t_cube_data *cube_data)
{
	int idx;

	idx = -1;
	if (cube_data->north_texture)
		free(cube_data->north_texture);
	if (cube_data->south_texture)
		free(cube_data->south_texture);
	if (cube_data->west_texture)
		free(cube_data->west_texture);
	if (cube_data->east_texture)
		free(cube_data->east_texture);
	if (cube_data->map)
	{
		while (cube_data->map[++idx])
			free(cube_data->map[idx]);
		free(cube_data->map);
	}
}
