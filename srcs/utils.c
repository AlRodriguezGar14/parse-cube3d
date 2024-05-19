/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:04:08 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/14 19:20:31 by dgomez-m         ###   ########.fr       */
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
	int *size;
	int *endian;
	int *bpp;
	void *ic;
	
	bpp = &data->textures[i].bpp;
	ic = data->textures[i].image_charge;
	size = &data->textures[i].line_s;
	endian = &data->textures[i].endian;
	data->textures[i].addres = mlx_get_data_addr(ic,bpp,size,endian);
}
bool load_textures_helper(t_cube_data *data, char *path, int i)
{
	//TODO : ft_strtrim from path because \n its not clean
	int width;
	int height;
	void *ic;
	
	if(!path)
	{
		data->textures[i].image_charge = mlx_new_image(data->mlx->mlx,W + 1,H +1);
		printf("hola amigo e i vale %d",i);
		return (false);
	}
	data->textures[i].image_charge = mlx_xpm_file_to_image(data->mlx->mlx,ft_strtrim(path,"\n"),&(width), &(height));
	if (!data->textures[i].image_charge) 
	{	
		printf ("no se carga bien xpm a image\n");
		printf("Hola soy el puntero de la mlx %p",data->mlx->mlx);
		return (true);
	}
	return (false);
}

void load_textures(t_cube_data *data)
{	
	
	//TODO: make a clean exit in true case ft_error or something
		if (load_textures_helper(data, data->east_texture, 0))
			return(exit(1));
		load_textures_helper(data, data->south_texture, 1);
		load_textures_helper(data, data->west_texture, 	2);
		load_textures_helper(data, data->north_texture, 3);
		load_textures_helper(data,NULL,4);
		get_addres_helper(data,0);
	 	get_addres_helper(data,1);
		get_addres_helper(data,2);
		get_addres_helper(data,3);
		get_addres_helper(data,4);
}
