/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:21:10 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/29 18:41:24 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSECUBE_H
# define PARSECUBE_H

# include "libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdbool.h>


#define A 65
#define D 68
#define W 87
#define S 83
//# define LEFT 0 // macos
# define LEFT 			97 // linux
//# define RIGHT 2 // macos
# define RIGHT 			100 // linux
//# define UP  13 // macos
# define UP  			119 // linux
//# define DOWN 1 // macos
# define DOWN 			115 // linux
# define ESC 			65307 // linux
# define TILE_SIZE 		100
# define FOV 			60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED	4
# define M_PI			3.14159265358979323846
# define W_S 800
# define H_S 600

typedef struct s_mlx {
	void    *mlx;
	void    *win;
	void	*img;
	void 	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}   t_mlx;

typedef struct s_player_position {
	int     x;
	int     y;
	int 	pos_x;
	int		pos_y;
	
	int 	rotation;
	char    orientation;
	double	angle;
	double 	fov;
	int left;
	int up;
}   t_player_position;

typedef struct s_image_info
{
	void	*image_charge;
	char 	*addres;
	int		bpp;
	int		line_s;
	int		endian;
	int		pxlc;
	int		pxlf;
	
	
} t_image_info;

typedef struct s_ray
{
	int		index;
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
	int		flag;
}	t_ray;

typedef struct s_cube_data {
	char    *north_texture; // no
	char    *south_texture; // so
	char    *west_texture; // we
	char    *east_texture; // e
	int     floor_color[3]; // f
	int     ceiling_color[3]; // c
	char    **map; // map
	int		max_y;
	int		max_x;
	t_player_position *player_position;
	t_mlx   *mlx;
	t_image_info *textures;
	t_ray *r;
}   t_cube_data;


# endif

// Path: validate_map.c
int validate_map(t_cube_data *cube_data, t_player_position *player_position);

// Path: validate_file.c
int validate_file(t_cube_data *cube_data);
int validate_extension(char *file);

// Path: utils.c
int ft_isspace(char c);
int double_pointer_len(char **ptr);
void load_textures(t_cube_data *data);

// Path: parsing_utils.c
void replace_tabs_with_spaces(char ***map);
int read_file(char *file, t_cube_data *cube_data);
char    *line_content(char *line);
void    free_double_pointer(char **ptr);


// Path: parsers.c
int		parse_line(char *line, t_cube_data *cube_data);
void    parse_map(char *line, t_cube_data *cube_data);
int		parse_colors(char *line, int color[3]);

// Path: movements.c
void	move_left(t_player_position *player_position);
void	move_right(t_player_position *player_position);
void	move_down(t_player_position *player_position);
void	move_up(t_player_position *player_position);

// PATH key_hook_terminal.c
int	key_hook_terminal(int keycode, t_cube_data *cube_data);

// Path: main.c
void    print_map(t_cube_data *cube_data);
void	print_game_terminal(t_cube_data *cube_data);

// Path: free_content.c
void	free_content(t_cube_data *cube_data);
void    free_mlx(t_mlx *mlx);

// Path: game.c

void	init_player(t_cube_data *data);
void	ray(t_cube_data *data);
int 	routine(void *d);
// Path: game_2.c
void	print_ray(t_cube_data *data, int draw[2], int x, int side);
void	init_ray(t_cube_data *data);
// Path: game_3.c
int get_pixel_color(int x, int y, t_image_info *img);
double	get_pixel_pos(t_image_info	*texture, t_cube_data *data);
// textures.c
int		rgb(int r, int g, int b);
void	print_c_f(t_cube_data *data);
void	my_mlx_pixel_put(t_image_info *data, int x, int y, int color);

// Key pressed
int key_pressed( int keycode ,void *param);
int key_release( int keycode ,void *param);

//get inter
float get_y_inter(t_cube_data *data, float ang);
float get_x_inter(t_cube_data *data, float ang);

//mini map
void paint_map(t_cube_data *data);
void ft_strlen_map(char **map , t_cube_data *data );