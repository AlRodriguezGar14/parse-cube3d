/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:21:10 by alberrod          #+#    #+#             */
/*   Updated: 2024/06/13 03:38:50 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSECUBE_H
# define PARSECUBE_H

# include "../mlx/mlx.h"
# include "libft.h"
# include <math.h>
# include <stdbool.h>

# define HEIGHT 1200
# define WIDTH 1804
# define A 97
# define D 100
# define W 119
# define S 115
# define LEFT 65361 // linux
# define RIGHT 65363 // linux
# define UP 65362 // linux
# define DOWN 65364 // linux
# define ESC 65307  // linux
# define TILE_SIZE 66
# define FOV 66
# define ROTATION_SPEED 0.042
# define PLAYER_SPEED 0.05
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define W_S 800
# define H_S 600
# define NORTH 1
# define SOUTH 3
# define EAST 0
# define WEST 2
# define TEXT_SIZE 64

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	void				*img_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct s_player_position
{
	int					x;
	int					y;
	int					pos_x;
	int					pos_y;

	int					rotation;
	char				orientation;
	double				angle;
	double				fov;

}						t_player_position;

typedef struct s_move
{
	int					mright;
	int					mleft;
	int					mup;
	int					mback;
	int					rright;
	int					rleft;
}						t_move;

typedef struct s_image_info
{
	void				*image_charge;
	char				*addres;
	int					bpp;
	int					line_s;
	int					endian;
	bool				created;
}						t_image_info;

typedef struct s_ray
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				ray_dir_x;
	double				ray_dir_y;
	double				perpwalldist;

}						t_ray;

typedef struct s_raycaster
{
	double				angle;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;

	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;

	double				end_x;
	double				end_y;
	int					color;
	int					side;

	int					map_x;
	int					map_y;

	int					step_x;
	int					step_y;
	double				wall_x;
}						t_raycaster;

typedef struct s_wall
{
	int					side;
	int					draw_start;
	int					draw_end;
	int					tex_x;
	int					tex_num;
	int					line_h;
	double				wallx;
	double				step;
	double				texpos;
	double				step_y;
	double				step_x;

}						t_wall;
typedef struct s_pos
{
	double				x;
	double				y;
}						t_pos;

typedef struct s_cube_data
{
	char *north_texture;  // no
	char *south_texture;  // so
	char *west_texture;   // we
	char *east_texture;   // e
	int floor_color[3];   // f
	int ceiling_color[3]; // c
	char **map;           // map
	int					max_y;
	int					max_x;
	t_player_position	*player_position;
	t_mlx				mlx;
	t_image_info		*textures;
	t_ray				r;
	t_move				move;
	t_wall				wall;
}						t_cube_data;

#endif

// Path: validate_map.c
int						validate_map(t_cube_data *cube_data,
							t_player_position *player_position);

// setter.c
void	set_initial_position(t_player_position *player_position, int x, int y,
		char orientation);

// Path: validate_file.c
int						validate_file(t_cube_data *cube_data);
int						validate_extension(char *file);

// Path: utils.c
int						ft_isspace(char c);
int						double_pointer_len(char **ptr);
void					load_textures(t_cube_data *data);
bool					load_textures_helper(t_cube_data *data, char *path,
							int i);
void					get_addres_helper(t_cube_data *data, int i);

// Path: parsing_utils.c
void					replace_tabs_with_spaces(char ***map, int idx);
int						read_file(char *file, t_cube_data *cube_data);
char					*line_content(char *line);
void					free_double_pointer(char **ptr);

// Path: parsers.c
int						parse_line(char *line, t_cube_data *cube_data);
void					parse_map(char *line, t_cube_data *cube_data);
int						parse_colors(char *line, int color[3]);

// Path: movements.c
void					move_left(t_player_position *player_position);
void					move_right(t_player_position *player_position);
void					move_down(t_player_position *player_position);
void					move_up(t_player_position *player_position);
int						moves(t_cube_data *d);
void					update_player_position(t_cube_data *data,
							double new_pos_x, double new_pos_y);
t_pos					calculate_new_position(t_cube_data *data, double move_x,
							double move_y);

// PATH key_hook_terminal.c
int						key_hook_terminal(int keycode, t_cube_data *cube_data);

//Path: print_terminal.c
void					print_map(t_cube_data *cube_data);
void	print_game_terminal(t_cube_data *cube_data, int crab_x, int crab_y);
// Path: free_content.c
void					free_content(t_cube_data *cube_data);
void					free_mlx(t_mlx *mlx);

// Path: game.c

void					init_player(t_cube_data *data);
int						ray(void *arg);
int						routine(void *d);
void					get_plyr_pos(t_cube_data *data);
// Path: img_getters.c
t_image_info			*get_texture(t_cube_data *data, int side);
int						get_texture_color(t_image_info *texture, int x, int y);
int						get_pixel_color(int x, int y, t_image_info *img);

// Path: init_ray.c
void					set_position(t_cube_data *data);
void					set_coordinates(t_raycaster *rc, t_cube_data *data);
int						set_camera_and_rays(t_raycaster *rc, int x,
							t_cube_data *data);
void					set_step_and_dist(t_raycaster *rc, t_cube_data *data);
// Path: wall.c
void					set_wall_dimensions(t_cube_data *data);
void					calculate_wall_x(t_raycaster *rc, t_cube_data *data);
void					dda_algorithm(t_raycaster *rc, t_cube_data *data);
// textures.c
int						rgb(int r, int g, int b);
void					print_c_f(t_cube_data *data);
// void	my_mlx_pixel_put(t_image_info *data, int x, int y, int color);
void					my_mlx_pixel_put(t_image_info *data, int x, int y,
							int color);
t_image_info			*renew_image(t_cube_data *data);

// Key pressed
int						key_pressed(int keycode, void *param);
int						key_release(int keycode, void *param);
int						destroy_window(void *param);
// mini map
void					paint_map(t_cube_data *data);
void					ft_strlen_map(char **map, t_cube_data *data);
