/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:04:08 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/11 03:11:37 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsecube.h"

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int double_pointer_len(char **ptr)
{
	int len;

	len = 0;
	while (ptr[len])
		len++;
	return (len);
}
//Funcion que busca texturas si no estan las pone definidas por default
void get_addres_helper(t_cube_data *data,int i)
{
	int size;
	int endian;
	int bpp;
	void *ic;
	
	bpp = data->textures[i].bpp;
	ic = data->textures[i].image_charge;
	size = data->textures[i].line_s;
	endian = data->textures[i].endian;
	data->textures[i].addres = mlx_get_data_addr(ic,&bpp,&size,&endian);
}
void load_textures_helper(t_cube_data *data, char *path, int i)
{
	int width;
	int height;
	void *ic;
		
	data->textures[i].image_charge = mlx_xpm_file_to_image(data->mlx->mlx,path,&(width), &(height));
}

void load_textures(t_cube_data *data)
{	
		load_textures_helper(data, data->north_texture, 0);
		load_textures_helper(data, data->south_texture, 1);
		load_textures_helper(data, data->west_texture, 	2);
		load_textures_helper(data, data->north_texture, 3);
		get_addres_helper(data,0);
	/* 	get_addres_helper(data,1);
		get_addres_helper(data,2);
		get_addres_helper(data,3); */
}
