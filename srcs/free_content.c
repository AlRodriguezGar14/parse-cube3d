/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:51:07 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/04 20:11:34 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

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
