/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:21:10 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/04 20:14:15 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSECUBE_H
# define PARSECUBE_H

# include "libft.h"
# include "../mlx/mlx.h"

//# define LEFT 0 // macos
# define LEFT 97 // linux
//# define RIGHT 2 // macos
# define RIGHT 100 // linux
//# define UP  13 // macos
# define UP  119 // linux
//# define DOWN 1 // macos
# define DOWN 115 // linux

# define ESC 65307 // linux

typedef struct s_mlx {
	void    *mlx;
	void    *win;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}   t_mlx;

typedef struct s_player_position {
	int     x;
	int     y;
	char    orientation;
}   t_player_position;

typedef struct s_cube_data {
	char    *north_texture; // no
	char    *south_texture; // so
	char    *west_texture; // we
	char    *east_texture; // ea
	int     floor_color[3]; // f
	int     ceiling_color[3]; // c
	char    **map; // map
	int		max_y;
	t_player_position *player_position;
	t_mlx   *mlx;
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

// Path: parsing_utils.c
void replace_tabs_with_spaces(char ***map);
int read_file(char *file, t_cube_data *cube_data);
char    *line_content(char *line);
void    free_double_pointer(char **ptr);


// Path: parsers.c
int parse_line(char *line, t_cube_data *cube_data);
void    parse_map(char *line, t_cube_data *cube_data);
int    parse_colors(char *line, int color[3]);

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
