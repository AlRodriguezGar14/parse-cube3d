/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 02:23:09 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	set_position(t_cube_data *data)
{
	if (!data->r.pos_x && !data->r.pos_y)
	{
		data->r.pos_x = (data->player_position->pos_x / TILE_SIZE) + 0.5;
		data->r.pos_y = (data->player_position->pos_y / TILE_SIZE) + 0.5;
	}
}

void	set_coordinates(t_raycaster *rc, t_cube_data *data)
{
	rc->angle = data->player_position->angle;
	rc->dir_x = cos(data->player_position->angle);
	rc->dir_y = sin(data->player_position->angle);
	rc->plane_x = 0.66 * rc->dir_y;
	rc->plane_y = -0.66 * rc->dir_x;
}

int	set_camera_and_rays(t_raycaster *rc, int x, t_cube_data *data)
{
	rc->camera_x = 2 * x / (double)WIDTH - 1;
	data->r.ray_dir_x = rc->dir_x + rc->plane_x * rc->camera_x;
	data->r.ray_dir_y = rc->dir_y + rc->plane_y * rc->camera_x;
	if (data->r.ray_dir_y == 0.0 || data->r.ray_dir_x == 0.0)
		return (1);
	rc->map_x = (int)data->r.pos_x;
	rc->map_y = (int)data->r.pos_y;
	rc->delta_dist_x = fabs(1 / data->r.ray_dir_x);
	rc->delta_dist_y = fabs(1 / data->r.ray_dir_y);
	return (0);
}

void	set_step_and_dist(t_raycaster *rc, t_cube_data *data)
{
	if (data->r.ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (data->r.pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - data->r.pos_x) * rc->delta_dist_x;
	}
	if (data->r.ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (data->r.pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - data->r.pos_y) * rc->delta_dist_y;
	}
}

void	init_player(t_cube_data *data)
{
	char	c;
	int		p_x;
	int		p_y;

	p_y = data->player_position->y;
	p_x = data->player_position->x;
	c = data->player_position->orientation;
	printf("c: %c\n", c);
	if (c == 'N')
		data->player_position->angle = 3 * M_PI / 2;
	if (c == 'S')
		data->player_position->angle = M_PI / 2;
	if (c == 'E')
		data->player_position->angle = M_PI * 2;
	if (c == 'W')
		data->player_position->angle = M_PI;
	data->player_position->pos_x = (p_x) + 0.5;
	data->player_position->pos_y = (p_y) + 0.5;
	data->player_position->fov = (FOV * M_PI / 180);
}
