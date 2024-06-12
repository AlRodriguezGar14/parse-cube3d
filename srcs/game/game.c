/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:12:58 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/12 14:20:46 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsecube.h"

void	draw_wall(t_cube_data *data, t_raycaster *rc, t_image_info *img, int x)
{
	t_image_info	*texture;
	int				tex_x;
	int				y;
	int				d;
	int				tex_y;

	texture = get_texture(data, rc->side);
	calculate_wall_x(rc, data);
	tex_x = (int)(rc->wall_x * (double)(64));
	if ((rc->side == 0 && data->r.ray_dir_x > 0) || (rc->side == 1
		&& data->r.ray_dir_y < 0))
		tex_x = 64 - tex_x - 1;
	y = data->wall.draw_start - 1;
	while (++y < data->wall.draw_end)
	{
		d = y * 256 - HEIGHT * 128 + data->wall.line_h * 128;
		tex_y = ((d * 64) / data->wall.line_h) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= 64)
			tex_y = 64;
		rc->color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(img, x, y, rc->color);
	}
}

void	draw_floor_and_ceiling(t_cube_data *data, t_image_info *img, int x)
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
		my_mlx_pixel_put(img, x, top, colors[floor]);
	}
	bottom = data->wall.draw_start + 1;
	while (--bottom != 0)
	{
		my_mlx_pixel_put(img, x, bottom, colors[ceiling]);
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
		set_wall_dimensions(data);
		draw_wall(data, &rc, img, x);
		draw_floor_and_ceiling(data, img, x);
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, img->image_charge,
		0, 0);
	mlx_destroy_image(data->mlx->mlx, img->image_charge);
	data->textures[4].created = false;
	return (0);
}
