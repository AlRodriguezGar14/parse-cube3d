/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:14:42 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/13 16:15:38 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

bool	texture_is_valid(int width, int height)
{
	if (width != TEXT_SIZE || height != TEXT_SIZE)
	{
		printf("Textures must be %dx%d\n", TEXT_SIZE, TEXT_SIZE);
		return (false);
	}
	return (true);
}

bool	load_textures_helper(t_cube_data *data, char *path, int i)
{
	int	width;
	int	height;

	if (!path)
	{
		if (i != 4)
			return (true);
		if (data->textures[i].created == true)
			return (false);
		data->textures[i].image_charge = mlx_new_image(data->mlx.mlx, WIDTH,
				HEIGHT);
		data->textures[i].created = true;
		return (false);
	}
	data->textures[i].image_charge = mlx_xpm_file_to_image(data->mlx.mlx, path,
			&(width), &(height));
	data->textures[i].created = true;
	if (!data->textures[i].image_charge)
	{
		printf("Can't load the textures\n");
		return (data->textures[i].created = false, true);
	}
	if (!texture_is_valid(width, height))
		return (true);
	return (false);
}

void	load_textures(t_cube_data *data)
{
	if (load_textures_helper(data, data->east_texture, 0))
		return ((void)destroy_window(data));
	if (load_textures_helper(data, data->south_texture, 1))
		return ((void)destroy_window(data));
	if (load_textures_helper(data, data->west_texture, 2))
		return ((void)destroy_window(data));
	if (load_textures_helper(data, data->north_texture, 3))
		return ((void)destroy_window(data));
	load_textures_helper(data, NULL, 4);
	get_addres_helper(data, 0);
	get_addres_helper(data, 1);
	get_addres_helper(data, 2);
	get_addres_helper(data, 3);
	get_addres_helper(data, 4);
}
