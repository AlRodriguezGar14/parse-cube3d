/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:04:08 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/12 17:54:29 by alberrod         ###   ########.fr       */
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
	// char *tmp;
	
	if(!path)
	{
		if (i != 4)
			return (true);
		if (data->textures[i].created == true)
			return (false);
		data->textures[i].image_charge = mlx_new_image(data->mlx->mlx,WIDTH,HEIGHT);
		data->textures[i].created = true;
		return (false);
	}
	// tmp = ft_strtrim(path,"\n");
	data->textures[i].image_charge = mlx_xpm_file_to_image(data->mlx->mlx,path,&(width), &(height));
	data->textures[i].created = true;
	// free(tmp);
	if (!data->textures[i].image_charge) 
	{	
		printf ("Can't load the textures\n");
		return (true);
	}
	return (false);
}

void load_textures(t_cube_data *data)
{	
	
	//TODO: make a clean exit in true case ft_error or something
		if (load_textures_helper(data, data->east_texture, 0))
			return(exit(1));
		if(load_textures_helper(data, data->south_texture, 1))
			return(exit(1));
		if(load_textures_helper(data, data->west_texture, 2))
			return(exit(1));
		if(load_textures_helper(data, data->north_texture, 3))
			return(exit(1));
		load_textures_helper(data,NULL,4);
		get_addres_helper(data,0);
	 	get_addres_helper(data,1);
		get_addres_helper(data,2);
		get_addres_helper(data,3);
		get_addres_helper(data,4);
}
