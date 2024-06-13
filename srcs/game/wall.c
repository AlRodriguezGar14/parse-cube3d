/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 02:30:09 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	set_wall_dimensions(t_cube_data *data)
{
	data->wall.line_h = (int)(HEIGHT / data->r.perpwalldist);
	data->wall.draw_start = -data->wall.line_h / 2 + HEIGHT / 2;
	if (data->wall.draw_start < 0)
		data->wall.draw_start = 0;
	data->wall.draw_end = data->wall.line_h / 2 + HEIGHT / 2;
	if (data->wall.draw_end >= HEIGHT)
		data->wall.draw_end = HEIGHT - 1;
}

void	calculate_wall_x(t_raycaster *rc, t_cube_data *data)
{
	if (rc->side == 0)
		rc->wall_x = data->r.pos_y + data->r.perpwalldist * data->r.ray_dir_y;
	else
		rc->wall_x = data->r.pos_x + data->r.perpwalldist * data->r.ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
}

static void	set_walldist(t_raycaster *rc, t_cube_data *data)
{
	double	numerator;

	if (rc->side == 0)
	{
		numerator = rc->map_x - data->r.pos_x + (1 - rc->step_x) / 2;
		data->r.perpwalldist = numerator / data->r.ray_dir_x;
	}
	else
	{
		numerator = rc->map_y - data->r.pos_y + (1 - rc->step_y) / 2;
		data->r.perpwalldist = numerator / data->r.ray_dir_y;
	}
	if (data->r.perpwalldist == 0.0)
		data->r.perpwalldist = 0.1;
}

static void	dda_step(t_raycaster *rc)
{
	if (rc->side_dist_x < rc->side_dist_y)
	{
		rc->side_dist_x += rc->delta_dist_x;
		rc->map_x += rc->step_x;
		rc->side = 0;
	}
	else
	{
		rc->side_dist_y += rc->delta_dist_y;
		rc->map_y += rc->step_y;
		rc->side = 1;
	}
}

void	dda_algorithm(t_raycaster *rc, t_cube_data *data)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		dda_step(rc);
		if (rc->map_y < 0 || rc->map_x < 0 || rc->map_y >= data->max_y
			|| rc->map_x >= data->max_x)
		{
			hit = true;
			break ;
		}
		if (data->map[rc->map_y][rc->map_x] == '1')
			hit = true;
	}
	set_walldist(rc, data);
}
