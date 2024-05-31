/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:41:55 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/05/25 01:40:22 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

int wall(t_cube_data *data, float x, float y)
{
	int m_x;
	int m_y;
	
	if(x < 0 || y < 0)
		return (0);
	m_x = floor(x / TILE_SIZE);
	m_y = floor(y / TILE_SIZE);
	if (m_y >= ft_atoi(data->map[m_y]) && m_x <= ft_strlen(data->map[m_y]))
		if(data->map[m_y][m_x] == '1')
			return (0);
	return (1);
	
}
int unit_circle(float ang, char c)
{
	if (c == 'x')
		if (ang > 0 && ang < M_PI)
			return (1);
	if (ang < M_PI / 2 || ang > 3 * M_PI / 2)
		return (1);
}
int check(float ang, float * inter , float * step, int is_hor)
{
	if (is_hor)
	{
		if (ang  > 0 && ang < M_PI)
		{
			*step += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else 
	{
		if(!(ang < M_PI / 2 || ang > 3 * M_PI / 2))
		{
			*step += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}	
	return (1);
}
float get_y_inter(t_cube_data *data, float ang)
{
	float x;
	float y;
	float x_step;
	float y_step;
	int pxl;
	
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(ang);
	
	y = floor(data->player_position->pos_y / TILE_SIZE) * TILE_SIZE;
	pxl = check (ang, &y, &y_step, 1);
	x = data->player_position->pos_x + (data->player_position->pos_y - y) / tan(ang);
	if (unit_circle(ang, 'x') && x_step > 0 || !unit_circle(ang, 'y') && x_step < 0)
		x_step *= -1;
	while(wall(data, x, y - pxl))
	{
		x += x_step;
		y += y_step;
	}
	
	return (sqrt(pow(data->player_position->pos_x - x, 2) + pow(data->player_position->pos_y - y, 2)));
	
}

float get_x_inter(t_cube_data *data, float ang)
{
	float x;
	float y;
	float x_step;
	float y_step;
	int pxl;
	
	x_step = TILE_SIZE;
	y_step = TILE_SIZE / tan(ang);
	
	y = floor(data->player_position->pos_y / TILE_SIZE) * TILE_SIZE;
	pxl = check (ang, &y, &y_step, 1);
	x = data->player_position->pos_x + (data->player_position->pos_y - y) / tan(ang);
	if (unit_circle(ang, 'x') && x_step > 0 || !unit_circle(ang, 'y') && x_step < 0)
		x_step *= -1;
	while(wall(data, x, y - pxl))
	{
		x += x_step;
		y += y_step;
	}
	
	return (sqrt(pow(data->player_position->pos_x - x, 2) + pow(data->player_position->pos_y - y, 2)));
	
}