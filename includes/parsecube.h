/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:21:10 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/04 02:16:23 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSECUBE_H
# define PARSECUBE_H

# include "libft.h"
# include "../mlx/mlx.h"

# define LEFT 0 
# define RIGHT 2 
# define UP  13
# define DOWN 1 

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
	char    *north_texture; // NO
	char    *south_texture; // SO
	char    *west_texture; // WE
	char    *east_texture; // EA
	int     floor_color[3]; // F
	int     ceiling_color[3]; // C
	char    **map; // MAP
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


// Path: parsers.c
int parse_line(char *line, t_cube_data *cube_data);
void    parse_map(char *line, t_cube_data *cube_data);
void    parse_colors(char *line, int color[3]);

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