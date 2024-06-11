/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:12:58 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/11 21:06:56 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

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

void	set_walldist(t_raycaster *rc, t_cube_data *data)
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

void	dda_algorithm(t_raycaster *rc, t_cube_data *data)
{
	bool	hit;

	hit = false;
	while (hit == false)
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

void	calculate_wall_x(t_raycaster *rc, t_cube_data *data)
{
	if (rc->side == 0)
		rc->wall_x = data->r.pos_y + data->r.perpwalldist * data->r.ray_dir_y;
	else
		rc->wall_x = data->r.pos_x + data->r.perpwalldist * data->r.ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
}

void	set_wall_dimensions(t_cube_data *data, t_raycaster *rc)
{
	data->wall.line_h = (int)(HEIGHT / data->r.perpwalldist);
	data->wall.draw_start = -data->wall.line_h / 2 + HEIGHT / 2;
	if (data->wall.draw_start < 0)
		data->wall.draw_start = 0;
	data->wall.draw_end = data->wall.line_h / 2 + HEIGHT / 2;
	if (data->wall.draw_end >= HEIGHT)
		data->wall.draw_end = HEIGHT - 1;
}

void	draw_wall(t_cube_data *data, t_raycaster *rc, t_image_info *img, int x)
{
	t_image_info	*texture;
	int				tex_x;
	int				y;
	int				d;
	int				tex_y;

	texture = get_texture(data, rc->side);
	calculate_wall_x(rc, data);
	tex_x = (int)(rc->wall_x * (double)(300));
	if ((rc->side == 0 && data->r.ray_dir_x > 0) || rc->side == 1
		&& data->r.ray_dir_y < 0)
		tex_x = 300 - tex_x - 1;
	y = data->wall.draw_start - 1;
	while (++y < data->wall.draw_end)
	{
		d = y * 256 - HEIGHT * 128 + data->wall.line_h * 128;
		tex_y = ((d * 300) / data->wall.line_h) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= 300)
			tex_y = 300;
		rc->color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(img, x, y, rc->color, WIDTH, HEIGHT);
	}
}

void	draw_floor_and_ceiling(t_cube_data *data, t_raycaster *rc,
		t_image_info *img, int x)
{
	int	colors[2];
	int	ceiling;
	int	floor;
	int	top;
	int	bottom;

	ceiling = 0;
	floor = 1;
	colors[ceiling] = rgb(data->ceiling_color[0], data->ceiling_color[1],
			data->ceiling_color[2]);
	colors[floor] = rgb(data->floor_color[0], data->floor_color[1],
			data->floor_color[2]);
	top = data->wall.draw_end;
	while (++top != HEIGHT)
	{
		my_mlx_pixel_put(img, x, top, colors[floor], WIDTH, HEIGHT);
	}
	bottom = data->wall.draw_start + 1;
	while (--bottom != 0)
	{
		my_mlx_pixel_put(img, x, bottom, colors[ceiling], WIDTH, HEIGHT);
	}
}

int	ray(void *arg)
{
	t_cube_data		*data;
	t_image_info	*img;
	t_raycaster		rc;
	int				x;

	data = (t_cube_data *)arg;
	moves(data);
	img = renew_image(data);
	set_position(data);
	set_coordinates(&rc, data);
	x = -1;
	while (++x < WIDTH)
	{
		if (set_camera_and_rays(&rc, x, data))
			return (1);
		set_step_and_dist(&rc, data);
		dda_algorithm(&rc, data);
		set_wall_dimensions(data, &rc);
		draw_wall(data, &rc, img, x);
		draw_floor_and_ceiling(data, &rc, img, x);
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, img->image_charge,
		0, 0);
	mlx_destroy_image(data->mlx->mlx, img->image_charge);
}

void	init_player(t_cube_data *data)
{
	char	c;
	int		p_x;
	int		p_y;

	p_y = data->player_position->y;
	p_x = data->player_position->x;
	c = data->player_position->orientation;
	if (c == 'N')
		data->player_position->angle = 3 * M_PI / 2;
	if (c == 'S')
		data->player_position->angle = M_PI / 2;
	if (c == 'E')
		data->player_position->angle = 0;
	if (c == 'W')
		data->player_position->angle = M_PI;
	data->player_position->pos_x = (p_x) + 0.5;
	data->player_position->pos_y = (p_y) + 0.5;
	data->player_position->fov = (FOV * M_PI / 180);
}
