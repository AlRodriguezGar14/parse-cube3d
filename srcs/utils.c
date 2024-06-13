/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:04:08 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/13 16:14:34 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	double_pointer_len(char **ptr)
{
	int	len;

	len = 0;
	while (ptr[len])
		len++;
	return (len);
}

void	get_addres_helper(t_cube_data *data, int i)
{
	int		*size;
	int		*endian;
	int		*bpp;
	void	*ic;

	bpp = &data->textures[i].bpp;
	ic = data->textures[i].image_charge;
	size = &data->textures[i].line_s;
	endian = &data->textures[i].endian;
	data->textures[i].addres = mlx_get_data_addr(ic, bpp, size, endian);
}
