/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 04:55:32 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	validate_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (ft_printf("Invalid file name\n"), 1);
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (ft_printf("Wrong file format\n"), 1);
	return (0);
}

int	validate_file(t_cube_data *cube_data)
{
	if (!cube_data->north_texture || !cube_data->south_texture
		|| !cube_data->west_texture || !cube_data->east_texture)
		return (ft_printf("Missing texture\n"), 1);
	if (cube_data->floor_color[0] < 0 || cube_data->floor_color[1] < 0
		|| cube_data->floor_color[2] < 0)
		return (ft_printf("Invalid floor color\n"), 1);
	if (cube_data->ceiling_color[0] < 0 || cube_data->ceiling_color[1] < 0
		|| cube_data->ceiling_color[2] < 0)
		return (ft_printf("Invalid ceiling color\n"), 1);
	if (!cube_data->map)
		return (ft_printf("Missing map\n"), 1);
	return (0);
}
