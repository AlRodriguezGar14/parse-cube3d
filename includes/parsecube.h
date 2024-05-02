/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:21:10 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/03 01:33:35 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSECUBE_H
# define PARSECUBE_H

# include "libft.h"
# include "../.mlx/mlx.h"

typedef struct s_mlx {
	void    *mlx;
	void    *win;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}   t_mlx;

typedef struct s_cube_data {
	char    *north_texture; // NO
	char    *south_texture; // SO
	char    *west_texture; // WE
	char    *east_texture; // EA
	int     floor_color[3]; // F
	int     ceiling_color[3]; // C
	char    **map; // MAP
}   t_cube_data;

typedef struct s_start_position {
	int     x;
	int     y;
	char    orientation;
}   t_start_position;

# endif

// Path: validate_map.c
int validate_map(t_cube_data *cube_data, t_start_position *start_position);

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
